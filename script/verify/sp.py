import sys
mfile = "NC_008253.fna"
mcc = 0
ml = 70*70556
lline = ''
dst = open('E10K.fa','w')
with open(mfile, 'r') as mfs:
  for mf in mfs:
    mcc += 1
    if mf[0] != '>' and len(mf) ==71:
      #dst.write(mf[:-1])
      lline += mf[:-1:]
      #print mf[:-1],mcc
      #if mcc > 2:
        #break
    #if mf[0] == 'C' or mf[0] == 'G' or mf[0] == 'T':
    #for iii in mf:
      #if iii == 'A' or iii == 'C' or iii == 'G' or iii == 'T':
        #dst.write(mf[:-1:])
      #print len(mf[:-1:])
dst.write(lline)
#print lline[201606:201606+20:],
print lline
lline +='\n'
dst.close()
