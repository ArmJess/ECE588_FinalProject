import random

file_object = open("input.txt","w")
rw=['R','W']
i=0
while i<1000:
    i=i+1
    pr_num=random.randrange(0,4,1)
    mem_loc=random.randrange(2,12,2)
    r_w=random.choice(rw)
    file_object.write(str(pr_num)+ ", "+str(mem_loc)+", "+str(i)+", "+str(r_w)+"\n")
    
file_object.close()