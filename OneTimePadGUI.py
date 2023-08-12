import tkinter as tk
from tkinter import filedialog
import subprocess
import os

# One-time pad encryption/decryption program GUI
# Requires onetimepad.exe to be in the same directory to work
# Version: v1.0, date: 12/08/2023
# https://github.com/TheNumber5/onetimepad-c

def open_file_dialog(entry):
    file_path = filedialog.askopenfilename()
    entry.delete(0, tk.END)
    entry.insert(0, file_path)
    check_enable_auto_buttons()

def auto_new_output():
    input_file = entry_input.get()
    if input_file:
        input_dir = os.path.dirname(input_file)
        input_filename, input_extension = os.path.splitext(os.path.basename(input_file))
        output_file = os.path.join(input_dir, f'output{input_extension}')
        entry_output.delete(0, tk.END)
        entry_output.insert(0, output_file)

def auto_new_key():
    input_file = entry_input.get()
    if input_file:
        input_dir = os.path.dirname(input_file)
        key_file = os.path.join(input_dir, 'key.bin')
        entry_key.delete(0, tk.END)
        entry_key.insert(0, key_file)

def check_enable_auto_buttons():
    input_file = entry_input.get()
    auto_new_output_button.config(state=tk.NORMAL if input_file else tk.DISABLED)
    auto_new_key_button.config(state=tk.NORMAL if input_file else tk.DISABLED)

def run_encryption_decryption():
    input_file = entry_input.get()
    output_file = entry_output.get()
    key_file = entry_key.get()
    mode = var_mode.get()

    if input_file and output_file and key_file:
        cmd_args = ['onetimepad.exe', mode, input_file, output_file, key_file]
        # Using a Python program to open a C program feels illegal
        subprocess.run(cmd_args)

root = tk.Tk()
root.title("One-Time Pad")

entry_input = tk.Entry(root, width=50)
entry_output = tk.Entry(root, width=50)
entry_key = tk.Entry(root, width=50)

button_input = tk.Button(root, text="Select Input File", command=lambda: open_file_dialog(entry_input))
button_output = tk.Button(root, text="Select Output File", command=lambda: open_file_dialog(entry_output))
button_key = tk.Button(root, text="Select Key File", command=lambda: open_file_dialog(entry_key))

auto_new_output_button = tk.Button(root, text="Auto new", command=auto_new_output, state=tk.DISABLED)
auto_new_key_button = tk.Button(root, text="Auto new", command=auto_new_key, state=tk.DISABLED)

var_mode = tk.StringVar()
var_mode.set("-e")
radio_encrypt = tk.Radiobutton(root, text="Encrypt", variable=var_mode, value="-e")
radio_decrypt = tk.Radiobutton(root, text="Decrypt", variable=var_mode, value="-d")

button_run = tk.Button(root, text="Run Encryption/Decryption", command=run_encryption_decryption)

entry_input.grid(row=0, column=0, padx=10, pady=10)
button_input.grid(row=0, column=1, padx=10, pady=10)

entry_output.grid(row=1, column=0, padx=10, pady=10)
button_output.grid(row=1, column=1, padx=10, pady=10)
auto_new_output_button.grid(row=1, column=2, padx=10, pady=10)

entry_key.grid(row=2, column=0, padx=10, pady=10)
button_key.grid(row=2, column=1, padx=10, pady=10)
auto_new_key_button.grid(row=2, column=2, padx=10, pady=10)

radio_encrypt.grid(row=3, column=0, padx=10, pady=5)
radio_decrypt.grid(row=3, column=1, padx=10, pady=5)

button_run.grid(row=4, columnspan=3, padx=10, pady=10)

root.mainloop()
