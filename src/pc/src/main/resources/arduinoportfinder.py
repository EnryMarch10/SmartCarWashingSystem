import sys, serial.tools.list_ports, re, os, subprocess

# Checks if pyserial is installed
python_manager = "pip"
lib_name = "pyserial"
lib_location = subprocess.run([python_manager, "show", lib_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

# Installing missing library
if lib_location.returncode != 0:   
    result = subprocess.run([python_manager, "install", lib_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    os.execl(sys.executable, sys.executable, *sys.argv)

# Adding installed library to global PATH variable
if lib_location.stdout.strip() not in sys.path:
    match = re.search(r'^Location: (.+)$', lib_location.stdout, re.MULTILINE)
    if match:
        lib_location = match.group(1)
        sys.path.append(lib_location)

# Writes out arduino uno ports, if more than 1 this could be a problem...
for port in list(serial.tools.list_ports.comports()):
    if "Arduino Uno" in port.description:
        print(port.name)
