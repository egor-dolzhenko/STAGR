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
 	entryTypes = ["qseqid", "sseqid", "pident", "length", "mismatch", "gapopen", "qstart", "qend", "sstart", "send", "evalue", "bitscore"]
	#outputVals = ["precursorName", "productName", "percentIdentity", "length", "mismatch", "gapopen", "precursorStart", "precursorEnd", "productStart", "productEnd", "expectedValue", "bitscore"]
	tr = {"qseqid":"precursorId", "sseqid":"productId", "pident":"percentIdentity", "length":"length", "mismatch":"mismatch", "gapopen":"gapopen", "qstart":"precursorStart", "qend":"precursorEnd", "sstart":"productStart", "send":"productEnd", "evalue":"expectedValue", "bitscore":"bitscore"}
	for line in blastnOutput.split('\n'):
		if line != '':
			record = {}
			for entryType, entry in zip(entryTypes,line.split('\t')):
				record[tr[entryType]] = convertToNumberIfPossible(entry)
			results.append(record)
	
	return results
	
def blat(blatOutput):
	results = []
 	entryTypes = ["qseqid", "sseqid", "pident", "length", "mismatch", "gapopen", "qstart", "qend", "sstart", "send", "evalue", "bitscore"]
	#outputVals = ["precursorName", "productName", "percentIdentity", "length", "mismatch", "gapopen", "precursorStart", "precursorEnd", "productStart", "productEnd", "expectedValue", "bitscore"]
	tr = {"qseqid":"precursorId", "sseqid":"productId", "pident":"percentIdentity", "length":"length", "mismatch":"mismatch", "gapopen":"gapopen", "qstart":"precursorStart", "qend":"precursorEnd", "sstart":"productStart", "send":"productEnd", "evalue":"expectedValue", "bitscore":"bitscore"}
	for line in blatOutput.split('\n'):
		if line != '':
			record = {}
			for entryType, entry in zip(entryTypes, line.split('\t')):
				record[tr[entryType]] = convertToNumberIfPossible(entry)
			results.append(record)
	
	return results