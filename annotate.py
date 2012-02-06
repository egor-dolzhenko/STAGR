import operator

def annotate(initialAlignment):
	#print initialAlignment
	#x = initialAlignment[0]
	print str(initialAlignment)
	return initialAlignment

# def annotate():
# 	blastnResultsFile = open("results")
# 	blastnResults = blastnResultsFile.read()
# 	qseqid = 0
# 	sseqid = 1
# 	pident = 2
# 	length = 3
# 	mismatch = 4
# 	gapopen = 5
# 	qstart = 6
# 	qend = 7
# 	sstart = 8
# 	send = 9
# 	evalue = 10
# 	bitscore = 11
# 	result = ""
# 	for blastnResult in blastnResults.split('\n'):
# 		print blastnResult.split('\t')
# 		if (blastnResult != "") and (int(blastnResult.split('\t')[length]) > 10000):
# 			result = result + blastnResult + '\n'
# 		
# 	result = result + '\n'
# 	print result[:-1]
# 	return result[:-1]
# 	pgaResultsFile = open("result")
# 	pgaResults = pgaResultsFile.read()
# 	qseqid = 0
# 	sseqid = 1
# 	pident = 2
# 	length = 3
# 	mismatch = 4
# 	gapopen = 5
# 	qstart = 6
# 	qend = 7
# 	sstart = 8
# 	send = 9
# 	evalue = 10
# 	bitscore = 11
# 	
# 	pgaMacStartIndex = 4
# 	pgaMacEndIndex = 5
# 	pgaMic1StartIndex = 6
# 	pgaMic1EndIndex = 7
# 	pgaMic2StartIndex = 8
# 	pgaMic2EndIndex = 9
# 	pgaMic1DirectionIndex = 10
# 	pgaMic2DirectionIndex = 11
# 	#listOfBreakpoints = []
# 	pgaMacStart = []
# 	pgaMacEnd = []
# 	pgaMic1Start = []
# 	pgaMic1End = []
# 	pgaMic2Start = []
# 	pgaMic2End = []
# 	pgaMic1Direction = []
# 	pgaMic2Direction = []
# 	
# 	for pgaResult in pgaResults.split("\n"):
# 		splitPgaResult = pgaResult.split(" ")
# 		if splitPgaResult != ['']:
# 			pgaMacStart.append(splitPgaResult[pgaMacStartIndex])
# 			pgaMacEnd.append(splitPgaResult[pgaMacEndIndex])
# 			pgaMic1Start.append(int(splitPgaResult[pgaMic1StartIndex]))
# 			pgaMic1End.append(int(splitPgaResult[pgaMic1EndIndex]))
# 			pgaMic2Start.append(int(splitPgaResult[pgaMic2StartIndex]))
# 			pgaMic2End.append(int(splitPgaResult[pgaMic2EndIndex]))
# 			pgaMic1Direction.append(splitPgaResult[pgaMic1DirectionIndex])
# 			pgaMic2Direction.append(splitPgaResult[pgaMic2DirectionIndex])
# 			#listOfBreakpoints.append([pgaMic1Start, pgaMic1End, pgaMic2Start, pgaMic2End, pgaMic1Direction, pgaMic2Direction])
# 			#print splitPgaResult[pgaMic1Start], " ", splitPgaResult[pgaMic1End]
# 	
# 	micStartLoci = {}
# 	micEndLoci = {}
# 	for i in range(len(pgaMic1Start)):
# 		micStartLoci[pgaMic1Start[i]] = i
# 		micStartLoci[pgaMic2Start[i]] = i
# 		micEndLoci[pgaMic1End[i]] = i
# 		micEndLoci[pgaMic2End[i]] = i
# 
# 	#print micStartLoci
# 	#sorted_micStartLoci = sorted(micStartLoci.iteritems(), key=operator.itemgetter(0))
# 	#print sorted_micStartLoci
# 	
# 	lastSeenDirection = ""
# 	constructingMds = True
# 	MDSs = []
# 	IESs = []
# 	lastSeenStart = 0;
# 	lastSeenEnd = 0;
# 	
# 	#print pgaMic1Direction[0]
# 	for start in sorted(micStartLoci.keys()):
# 		
# 		index = micStartLoci[start]
# 		print start
# 		print pgaMic1Direction[index]
# 		print pgaMic2Direction[index]
# 		#print lastSeenDirection
# 		
# 		if (lastSeenDirection == ""):
# 			if pgaMic1Start[index] == start:
# 				if pgaMic1Direction[index] == "L":
# 					#print 1
# 					MDSs.append(("?", pgaMic1End[index]))
# 				else:
# 					#print 2
# 					pass
# 				lastSeenStart = pgaMic1Start[index]
# 				lastSeenEnd = pgaMic1End[index]
# 				lastSeenDirection = pgaMic1Direction[index]
# 				continue
# 			elif pgaMic2Start[index] == start:
# 				if pgaMic2Direction[index] == "L":
# 					#print 3
# 					MDSs.append(("?", pgaMic2End[index]))
# 				else:
# 					#print 4
# 					pass
# 				lastSeenStart = pgaMic2Start[index]
# 				lastSeenEnd = pgaMic2End[index]
# 				lastSeenDirection = pgaMic2Direction[index]
# 				continue
# 			else:
# 				print "Error"
# 		
# 		if (pgaMic1Start[index] == start):
# 			if lastSeenDirection == "R":
# 				if pgaMic1Direction[index] == "R":
# 					#print 1
# 					MDSs.append((lastSeenStart, "?"))
# 					lastSeenDirection = "R"
# 					#continue
# 				else:
# 					MDSs.append((lastSeenStart, pgaMic1End[index]))
# 					#print 2
# 					lastSeenDirection = "L"
# 					#continue
# 			elif lastSeenDirection == "L":
# 				if pgaMic1Direction[index] == "R":
# 					#print 3
# 					IESs.append((lastSeenEnd, pgaMic1Start[index]))
# 					lastSeenDirection = "R"
# 					#continue
# 				else:
# 					#print 4
# 					MDSs.append(("?", pgaMic1End[index]))
# 					IESs.append((lastSeenEnd, "?"))
# 					lastSeenDirection = "L"
# 					#continue
# 			lastSeenStart = pgaMic1Start[index]
# 			lastSeenEnd = pgaMic1End[index]	
# 		elif (pgaMic2Start[index] == start):
# 			if lastSeenDirection == "R":
# 				if pgaMic2Direction[index] == "R":
# 					MDSs.append((lastSeenStart, "?"))
# 					IESs.append(("?", pgaMic2Start[index]))
# 					lastSeenDirection = "R"
# 					#continue
# 				else:
# 					MDSs.append((lastSeenStart, pgaMic2End[index]))
# 					lastSeenDirection = "L"
# 					#continue
# 			elif lastSeenDirection == "L":
# 				if pgaMic2Direction[index] == "R":
# 					IESs.append((lastSeenEnd, pgaMic2End[index]))
# 					lastSeenDirection = "R"
# 					#continue
# 				else:
# 					MDSs.append(("?", pgaMic2End[index]))
# 					IESs.append((lastSeenEnd, "?"))
# 					lastSeenDirection = "L"	
# 					#continue
# 			lastSeenStart = pgaMic2Start[index]
# 			lastSeenEnd = pgaMic2End[index]
# 		else:
# 			print "Error"
# 		#if (lastSeenDirection == ):
# 		#	print ""
# 	
# 	result = ""
# 	for mds in MDSs:
# 		#print mds
# 		mdsStart = mds[0]
# 		mdsEnd = mds[1]
# 		if mdsStart != "?":
# 			index1 = micStartLoci[mdsStart]
# 			index2 = micEndLoci[mdsEnd]
# 			
# 			if(pgaMacStart[index1] < pgaMacEnd[index2]):
# 				macStart = pgaMacStart[index1]
# 				macEnd = pgaMacEnd[index2]
# 			else:
# 				macStart = pgaMacStart[index2]
# 				macEnd = pgaMacEnd[index1]
# 			result = result + "MAC\t" + "MIC\t" + "100\t" + str(mdsEnd - mdsStart) + "\t"+"0\t" + "0\t" + str(macStart) + "\t" + str(macEnd) + "\t" + str(mdsStart) + "\t" + str(mdsEnd) + "\t" + "0\t" + "100" + "\n"
# 	print result
# 	return result
