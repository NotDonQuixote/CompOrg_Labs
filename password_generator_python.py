import random
import tkinter

def pwgenpt1():
    inputbox = tkinter.Entry(root, font=("Times new Roman", 14))

    pw_len = slidervalue.get()
    password = []
    password_string = ""
    for i in range(0, int(pw_len)):
        chartype = random.randint(0, 3)
        password.append(chargen(chartype))
    for char in password:
        print(char, end='')
    password_string = password_string.join([str(char) for char in password])
    print(f"\nGenerated password: {password_string}")
    password_label = tkinter.Label(root, text=f"Generated password: {password_string}",
                                    font=("Times new Roman", 14), bg="white", fg=button_color)
    password_label.pack(padx=20, pady=20)

def chargen(x):
    num = [0,1,2,3,4,5,6,7,8,9,0]
    upper = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    lower = ['q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m']
    spec_char = ['!','@','#','$','%','^','&','*','(',')','<','>','_','+','-','=']
    
    vals = [num, upper, lower, spec_char]
    char = vals[x][random.randint(0, len(vals[x])-1)]
    return(char)

button_color = "#8300c9"
background_color = "#130019"
second_color = "#FF0084"
blue = "#8695e0"

root = tkinter.Tk()
root.title("Password Generator")
root.minsize(400, 400)
root.geometry("400x400")
label = tkinter.Label(root, text="Password Generator", font=("Times new Roman", 20), bg="white", fg=button_color)
label.pack(padx=20, pady=20)

include_entry = tkinter.Entry(root)
include_entry.pack()

slidervalue = tkinter.IntVar()
slider = tkinter.Scale(root, width=100, from_=8, to=30, orient=tkinter.HORIZONTAL, 
                           font=("Times new Roman", 14), variable=slidervalue, label="Password Length", bg=background_color, fg=button_color)
slider.pack(padx=20, pady=80)

button = tkinter.Button(root, text="Generate me a password!", 
                        background=second_color, font=("Times new Roman", 14), command=pwgenpt1)
button.pack(padx=10, pady=10)
quit_button = tkinter.Button(root, text= "Quit",
                              background=blue, font=("Times new Roman", 12), command=root.destroy)

quit_button.place(x=50, y=400)
quit_button.pack()

root.mainloop()
