#!/usr/bin/python
import random, sys
import argparse

def main():
    version_msg = "%prog 8.30"
    description_msg ="""Write a random permutation of the
 input lines to standard output.
With no FILE, or when FILE is -,
 read standard input."""

    parser = argparse.ArgumentParser(version=version_msg, description=description_msg)
    parser.add_argument("-i", "--input-range", metavar="lo-hi")
    parser.add_argument("-n", "--head-count", metavar="count")
    parser.add_argument("-r", "--repeat", action="store_true")
    parser.add_argument("inputfile", type=argparse.FileType("r"),
                        nargs="?", default=sys.stdin)
    args = parser.parse_args(sys.argv[1:])
    count = args.head_count

    if count==None:
        count=-1
    else:
        try:
            count=int(count)
        except:
            parser.error("error!")
    if args.input_range!=None:
        arr=args.input_range.split('-',1)
        try:
            tou=int(arr[0])
            wei=int(arr[1])
        except:
            parser.error("error!")
             
        if args.repeat==False:
            zhencount=wei-tou+1
            li=[]
            x=tou
            while x<=wei:
			li.append(int(x))
			x=x+1
            if count==-1:
                newli=random.sample(li, zhencount)
            else:
                newli=random.sample(li, count)
            for i in newli:
                sys.stdout.write(str(i) + '\n')
        else:
            while count!=0:
                sys.stdout.write(str(random.choice(range(tou,wei+1))) + '\n')
                count-=1
                  
            
        


    else:
        li=[]
        if args.inputfile==sys.stdin:
            li=args.inputfile.readlines()
        else:
            wd=open(args.inputfile.name)
            li=wd.readlines()
            wd.close()
        if args.repeat==False:
            chu = []
            if count==-1:
                count=len(li)

            chu=random.sample(li,count)
            for i in chu:
                sys.stdout.write(str(i))
        else:
            if count==-1:
                while True:
                    sys.stdout.write(str(random.choice(chu)))
            else:
                while count!=0:
                    sys.stdout.write(str(random.choice(chu)))
                    n-=1

        
if __name__ == "__main__":
    main()
