def convertToNumberIfPossible(num):
	try:
		return int(num)
	except ValueError:
		try:
			return float(num)
		except ValueError:
			return num

def blastn(blastnOutput):
	results = []
 	entryTypes = ['qseqid', 'sseqid', 'pident', 'length', 'mismatch', 'gapopen', 'qstart', 'qend', 'sstart', 'send', 'evalue', 'bitscore']
	outputVals = ["queryName", "subjectName", "percentIdentity", "length", "mismatch", "gapopen", "queryStart", "queryEnd", "subjectStart", "subjectEnd", "expectedValue", "bitscore"]
	for line in blastnOutput.split('\n'):
		if line != '':
			record = {}
			for entryType, entry in zip(entryTypes,line.split('\t')):
				record[entryType] = convertToNumberIfPossible(entry)
			results.append(record)
	
	return results
	
def blat(blatOutput):
	results = []
 	entryTypes = ['qseqid', 'sseqid', 'pident', 'length', 'mismatch', 'gapopen', 'qstart', 'qend', 'sstart', 'send', 'evalue', 'bitscore']
	outputVals = ["queryName", "subjectName", "percentIdentity", "length", "mismatch", "gapopen", "queryStart", "queryEnd", "subjectStart", "subjectEnd", "expectedValue", "bitscore"]
	for line in blatOutput.split('\n'):
		if line != '':
			record = {}
			for entryType, entry in zip(entryTypes, line.split('\t')):
				record[entryType] = convertToNumberIfPossible(entry)
			results.append(record)
	
	return results