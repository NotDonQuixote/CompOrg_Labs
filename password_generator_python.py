import random
def main():
    pw_len = input("please enter the password length: ")
    password = []
    
    for i in range(0, int(pw_len)):
        chartype = random.randint(0, 3)
        password.append(chargen(chartype))
    for char in password:
        print(char, end='')
        
def chargen(x):
    
    num = [0,1,2,3,4,5,6,7,8,9,0]
    upper = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    lower = ['q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m']
    spec_char = ['!','@','#','$','%','^','&','*','(',')','<','>','_','+','-','=']
    
    vals = [num, upper, lower, spec_char]
    char = vals[x][random.randint(0, len(vals[x])-1)]
    return(char)





main()
