#generate a sudoku puzzle
import numpy as np
import random
from tkinter import *

def swap_cols(arr, frm, to):
    arr[:,[frm, to]] = arr[:,[to, frm]]
    
def swap_rows(arr, frm, to):
    arr[[frm, to],:] = arr[[to, frm],:]

def swap_cols_strip(arr,strip1,strip2):
    swap_cols(arr,(strip1*3),(strip2*3))
    swap_cols(arr,(strip1*3)+1,(strip2*3)+1)
    swap_cols(arr,(strip1*3)+2,(strip2*3)+2)

def swap_rows_strip(arr,strip1,strip2):
    swap_rows(arr,(strip1*3),(strip2*3))
    swap_rows(arr,(strip1*3)+1,(strip2*3)+1)
    swap_rows(arr,(strip1*3)+2,(strip2*3)+2)

def swap_rows_in_strip(arr,strip_number,row1,row2):
    swap_rows(arr,strip_number*3+row1,strip_number*3+row2)

def swap_cols_in_strip(arr,strip_number,col1,col2):
    swap_cols(arr,strip_number*3+col1,strip_number*3+col2)
    
def fill_matrix():
    array = list(range(1,10))
    random.shuffle(array)
    source = np.array(array)
    result = np.zeros(shape=(9,9))
    for i in range(9):
        strip_number = i//3
        result[i]=(np.roll(source,i*3+strip_number))
    return result

#entry point
function_list = [swap_cols_strip,swap_rows_strip,swap_rows_in_strip,swap_cols_in_strip,np.transpose]
arr = fill_matrix()
for i in range(50):
    randnum = random.randint(0,len(function_list)-1)
    if(randnum==0 or randnum ==1):
        st1 = random.randint(0,2)
        st2 = random.randint(0,2)
        function_list[randnum](arr,st1,st2)
    elif(randnum==2 or randnum==3):
        e1 = random.randint(0,2)
        e2 = random.randint(0,2)
        st = random.randint(0,2)
        function_list[randnum](arr,st,e1,e2)
    else:
        function_list[randnum](arr)
    print (function_list[randnum].__name__)
print (arr)
root = Tk()
c = Canvas(root,width=500,height=500,bg='white')
c.pack()
left_bound=0
down_bound=0
sector_color1='#aaaaaa'
sector_color2='#777777'
for i in range(9):
    for j in range(9):
        if(((i>2 and i<6) or (j>2 and j<6)) and not((i>2 and i<6) and (j>2 and j<6))):
            color = sector_color1
        else:
            color = sector_color2
        c.create_rectangle(left_bound,down_bound,left_bound+50,down_bound+50,fill=color)
        rect_center_x = left_bound +25
        rect_center_y = down_bound +25
        c.create_text(rect_center_x,rect_center_y,anchor='center',text=str(int(arr[i][j])))
        left_bound+=50
    left_bound=0
    down_bound+=50
root.mainloop()
