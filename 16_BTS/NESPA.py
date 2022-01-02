#-------------------------------------------------------------------------------
# Purpose:     2021 Prof. Zoh's Work     "李⑺븯寃� �댁� 留먯옄."
# Author:      Cho
# Created:     2021-11-16
#-------------------------------------------------------------------------------
# ���� �뚯씪�먯꽌 \n 怨듬갚�� 臾댁떆�⑸땲��.
# �ъ슜踰�
# > python NESPA.py  myBTS.cpp

import sys
import os


myfile = sys.argv[1]  # �ш린瑜� 痢≪젙�� ���� �뚯씪

if len(sys.argv) != 2:
    print(" Usage: > python NESPA.py  mycode.cpp")
    print(" NESPA size瑜� 痢≪젙�� �뚯씪�� 媛�닔�� 1媛쒕쭔 媛���")
    sys.exit()

print(" NESPA �ш린瑜� 痢≪젙�� �뚯씪 = ", myfile )

if ( not os.path.isfile( myfile ) ) :
    print(f' �ㅻ쪟 FILE: <{ myfile }>�� �놁뒿�덈떎. 醫낅즺 ��')
    exit(0)
else :
    f = open( myfile, 'r')

mydata = f.read( )
print(" �뚯씪�� 臾쇰━�� �ш린 = ",  len(mydata))
Lines = mydata.split( )
Sines = map( len, Lines )
print(f"\n {myfile} �뚯씪�� NESPA �ш린 = {sum(Sines)} ")