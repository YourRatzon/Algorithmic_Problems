import string

def solve(st):
    intab = string.lowercase
    outtab = string.lowercase[2:] + "ab"
    trantab = string.maketrans(intab, outtab)
    print (st.translate(trantab))

if __name__ == '__main__':
    st = ("g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp."
          " bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm "
          "jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj.")
    solve(st)
    solve("map")
