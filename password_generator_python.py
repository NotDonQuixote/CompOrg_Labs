import random
import tkinter

button_color = "#8300c9"
background_color = "#130019"
WIN_W, WIN_H = 800, 550

'''class window(tkinter.Tk):
    def __init__(self, master):
        super().__init__(
            master, width=WIN_W, height=WIN_H,
            bg=background_color
        )

    def make_button(self, text, command, x, y):
        button = tkinter.Button(
            self, text=text, command=command,
            bg=button_color, fg="white",
            font=("Times new Roman", 16),
            relief="raised", bd=0
        )
        button.place(x=x, y=y)
'''
root = tkinter.Tk()
root.title("Password Generator")
root.minsize(400, 400)
root.geometry("300x300+50+50")

tkinter.Label(root, text="enter password length").pack()
tkinter.Label(root, text="Test text").pack()
tkinter.Button(anchor="center",text="Button test")

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

#main()
root.mainloop()


