#Standard ACL
import ipaddress
import sys

class ACL:
	def __init__(self, aclFile, packetsFile, aclType):
		self.acl = []
		self.rawPackets = []
		self.packets = []
		self.output = []
		self.networks = []

		self.aclType = aclType

		#Used to store the values in the acl rules
		self.mask = 0
		self.addr = 0
		#Addtional values for extended rules
		self.dstAddr = 0
		self.dstMask = 0
		self.port = 0

		#Read in ACL rules
		with open(aclFile) as file:
			for line in file:
				line = line.strip("\\\n")
				line = line.split()
				if line != []:
					self.acl.append(line)

		if self.aclType == 'standard':
		#Read in Packets for normal
			with open(packetsFile) as file:
				for line in file:
					line = line.strip("\\\n")
					self.rawPackets.append(line)

			#Change Packets to IPv4
			for addr in self.rawPackets:
				value = int(ipaddress.ip_address(unicode(addr)))
				self.packets.append(value)

		if self.aclType == 'extended':
		#Read in packets for extended
			with open(packetsFile) as file:
				for line in file:
					line = line.strip("\\\n")
					line = line.split()
					self.rawPackets.append(line)

			#Change Packets to IPv4
			for addr in self.rawPackets:
				temp = []
				i = 0
				while i < 2:
					value = int(ipaddress.ip_address(unicode(addr[i])))
					temp.append(value)
					i = i+1
				temp.append(addr[2])
				self.packets.append(temp)

		print 'ACL Rules:'
		for element in self.acl:
			print element

		print '\nIncoming Packets: ', self.rawPackets

		print "\nACL ready to run....\n"

		if self.aclType == 'standard':
			i = -1
			for packet in self.packets:
				i = i+1
				for rule in self.acl:
					#The Acl is of type "Permit Any"
					if len(rule) == 4:
						self.convertStandard('0.0.0.0', '0.0.0.0')

					#The ACL is normal form
					else:
						self.convertStandard(rule[3], rule[4])

					flag = rule[2]

					if self.checkStandard(self.addr, self.mask, packet):
						if flag == 'deny':
							temp = self.rawPackets[i]
							temp = temp + ' denied'
							self.output.append(temp)
							break
						elif flag == 'permit':
							temp = self.rawPackets[i]
							temp = temp + ' permitted'
							self.output.append(temp)
							break
						elif flag == 'permit' and rule[3] == 'any':
							temp = self.rawPackets[i]
							temp = temp + ' permitted'
							self.output.append(temp)
							break

			print self.output


		elif self.aclType == 'extended':
			i = -1
			for packet in self.packets:
				i = i+1
				for rule in self.acl:
					#Different statements for different types of extended ACLs
					#len 8 Example = "access-list 101 permit tcp any any Eq 22"
					if len(rule) == 8:
						flag = rule[2]
						port = self.determinePort(packet[2])
						if flag == 'permit':
							if (rule[4] and rule[5] == 'any'):
								if port == int(rule[7]):
									temp = self.rawPackets[i]
									temp.append("permitted")
									self.output.append(temp)
									break
							else:
								self.output.append('Invalid ACL Rule')
								break

					#len 9 Example = "access-list 101 permit tcp any 127.0.0.0 0.255.255.255 Eq 22"
					# or "access-list 101 permit tcp 172.0.0.0 0.255.255.255 any Eq 22"
					elif len(rule) == 9:
						flag = rule[2]
						if rule[4] == 'any':
							self.convertExtended3(rule[5], rule[6])
							port = self.determinePort(packet[2]) 
							if self.checkExtended1(self.dstAddr, self.dstMask, rule[8], packet[1], port):
								if flag == 'permit':
									temp = self.rawPackets[i]
									temp.append("permitted")
									self.output.append(temp)
									break
								if flag == 'deny':
									temp = self.rawPackets[i]
									temp.append("denied")
									self.output.append(temp)
									break

						elif rule[6] == 'any':
							self.convertExtended2(rule[4], rule[5])
							port = self.determinePort(packet[2]) 
							if self.checkExtended1(self.addr, self.mask, rule[8], packet[0], port):
								print 'Success'
								if flag == 'permit':
									temp = self.rawPackets[i]
									temp.append("permitted")
									self.output.append(temp)
									break
								if flag == 'deny':
									temp = self.rawPackets[i]
									temp.append("denied")
									self.output.append(temp)
									break

					#len 10 Example = "access-list 101 permit tcp 127.14.23.0 0.0.0.255 172.234.4.2 0.0.0.0 Eq 22"
					elif len(rule) == 10:
						self.convertExtended1(rule[4], rule[5], rule[6], rule[7])
						flag = rule[2]
						port = self.determinePort(packet[2])
						if self.checkExtended2(self.addr, self.mask, self.dstAddr, self.dstMask, rule[9], packet[0], packet[1], port):
							if flag == 'permit':
								temp = self.rawPackets[i]
								temp.append("permitted")
								self.output.append(temp)
								break

							elif flag == 'deny':
								temp = self.rawPackets[i]
								temp.append('denied')
								self.output.append(temp)
								break



			print self.output


	#access-list, 102, deny, tcp, 172.16.4.13, 0.0.0.0, 172.16.3.0, 0.0.0.255, 9

	#Confirm what the acl takes on friday
	def convertStandard(self, addr, mask):
		self.addr = int(ipaddress.ip_address(unicode(addr)))
		self.mask = int(ipaddress.ip_address(unicode(mask)))

	def convertExtended1(self, addr, mask, dstAddr, dstMask):
		self.addr = int(ipaddress.ip_address(unicode(addr)))
		self.mask = int(ipaddress.ip_address(unicode(mask)))

		self.dstAddr = int(ipaddress.ip_address(unicode(dstAddr)))
		self.dstMask = int(ipaddress.ip_address(unicode(dstMask)))

	def convertExtended2(self, addr, mask):
		self.addr = int(ipaddress.ip_address(unicode(addr)))
		self.mask = int(ipaddress.ip_address(unicode(mask)))

	def convertExtended3(self, dstAddr, dstMask):
		self.dstAddr = int(ipaddress.ip_address(unicode(dstAddr)))
		self.dstMask = int(ipaddress.ip_address(unicode(dstMask)))

	def checkStandard(self, addr, mask, inAddr):
		if mask == 0 and addr == 0:
			return True
		else:
			return (inAddr >= addr and inAddr <= (addr + mask))

	def checkExtended1(self, addr, mask, rulePort, ip, packetPort):
		rulePort = int(rulePort)
		if (ip >= addr and ip <= addr + mask and (rulePort == packetPort)):
			return True
		else:
			return False

	def checkExtended2(self, addr, mask, dstAddr, dstMask, rulePort, src, dst, packetPort):
		#All we need to do is determine if the src and dst of the packet is within the
		#src and dst networks specified by the ACL rule
		if (src >= addr and src <= addr + mask):
			if (dst >= dstAddr and dst <= dstAddr + dstMask):
				if int(rulePort) == packetPort:
					return True

		return False

	def determinePort(self, port):
		if port == 'FTP': 
			return 20
		elif port == 'SSH' : 
			return 22
		elif port == 'Telnet' : 
			return 23
		elif port == 'SMTP' : 
			return 25
		elif port == 'DNS' : 
			return 53
		elif port == 'HTTP' : 
			return 80
		elif port == 'SNMP' : 
			return 161

if __name__ == "__main__":

    engine = ACL('A1/extendedAcl', 'A1/extendedPackets', 'extended')



