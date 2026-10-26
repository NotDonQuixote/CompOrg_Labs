import random
import tkinter

button_color = "#8300c9"
background_color = "#130019"
blue = "#8695e0"
neonblue = "#00ffff"
bluegreen = "#00ffcc"
orange = "#ff7f00"
pink = "#ff00ff"

def pwgenpt1(include_entry):
    #print("test")
    #print(include_entry.get())
    pw_len = slidervalue.get()
    entryspot = 0
    if include_entry.get() == "":
            pw_len = slidervalue.get()
    else:
        #print(include_entry.get())
        entryspot = random.randint(0, (pw_len - len(include_entry.get())))
        #print("entry stpot: ", entryspot)
    
    #print("entry stpot: ", entryspot)
    password = [''] * int(pw_len)
    password[entryspot] = include_entry.get()
    global password_string
    password_string = ""
    for i in range(0, int(pw_len)):
        if (password[i] != ''): #ignores user entry
             continue
        chartype = random.randint(0, 3)
        password[i] = chargen(chartype)
    password_string = password_string.join([str(char) for char in password])
    password_label.config(text=f"Generated password: {password_string}")
    #print(f"\nGenerated password: {password_string}")

def chargen(x):
    num = [0,1,2,3,4,5,6,7,8,9,0]
    upper = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    lower = ['q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m']
    spec_char = ['!','@','#','$','%','^','&','*','(',')','<','>','_','+','-','=']
    
    vals = [num, upper, lower, spec_char]
    char = vals[x][random.randint(0, len(vals[x])-1)]
    return(char)

def copy_to_clipboard(text): #will reuse for later functinos so dont make the variable password_string
    root.clipboard_clear()
    root.clipboard_append(text)
    root.update()

root = tkinter.Tk()
root.title("Password Generator")
root.configure(bg=background_color)
root.minsize(480, 480)
root.geometry("480x480")
label = tkinter.Label(root, text="Password Generator", font=("Times new Roman", 20), bg=background_color, fg=button_color)
label.pack(padx=20, pady=20)

include_entry = tkinter.Entry(root)
include_entry.pack()

slidervalue = tkinter.IntVar()
slider = tkinter.Scale(root, from_=8, to=30, orient=tkinter.HORIZONTAL, 
                           font=("Times new Roman", 14), variable=slidervalue, label="Password Length", bg=background_color, fg=button_color)
slider.pack(ipadx=60, ipady=20)

button = tkinter.Button(root, text="Generate me a password!", 
                        background=button_color, font=("Times new Roman", 14), command=lambda: pwgenpt1(include_entry))
button.pack(padx=10, pady=10)
copy_button = tkinter.Button(root, text="Copy to clipboard",
                            background=bluegreen, font=("Times new Roman", 12), command=lambda: copy_to_clipboard(password_string))
copy_button.pack(padx=10, pady=10)
quit_button = tkinter.Button(root, text= "Quit",
                              background=blue, font=("Times new Roman", 12), command=root.destroy)

password_label = tkinter.Label(root, text="",
                                    font=("Times new Roman", 14), bg=background_color, fg=bluegreen)
password_label.pack(padx=20, pady=20)

quit_button.place(x=50, y=400)
quit_button.pack()

root.mainloop()
