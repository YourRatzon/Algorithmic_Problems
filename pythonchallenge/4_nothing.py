import re
from urllib import request

def solve():
    url = "http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing="
    html = "12345"
    for i in range(400):
        r = request.urlopen(url+html[-5:])
        bytecode = r.read()
        html = bytecode.decode()
        print ("{}: {}".format(i+1,html))
        html = re.search(r"(\d+)$", html, re.MULTILINE).groups()[0]
        if (int(html)) == 16044:
            html = "8022"

if __name__ == '__main__':

    solve()
