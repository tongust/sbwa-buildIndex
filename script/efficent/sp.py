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
      lline += mf[:-1:]
dst.write(lline)
#print lline[201606:201606+20:],
print lline
lline +='\n'
dst.close()
