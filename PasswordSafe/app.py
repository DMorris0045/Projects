import keyring
from getpass import getpass

SERVICE = "MyPasswordVault"  # namespace in the OS keychain

#add website, username, and password to keep safe
def add_entry():
    site = input("Website: ").strip()
    user = input("Username: ").strip()
    pwd = getpass("Password (hidden): ")
    keyring.set_password(f"{SERVICE}:{site}", user, pwd)
    print("Saved securely in the OS keychain.")

#to view an entry, input website and username
def view_entry():
    site = input("Website: ").strip()
    user = input("Username: ").strip()
    pwd = keyring.get_password(f"{SERVICE}:{site}", user)  # only two args
    if pwd is None:
        print("No entry found for that website/username.")
    else:
        print(f"Password for {site}/{user}: {pwd}")

def main():

    #loop continues unless quit is chosen
    while True:
        print("\n1) Add  2) View  3) Quit")
        choice = input("Choose: ").strip()
        if choice == "1": #1 calls add_entry method
            add_entry()
        elif choice == "2":
            view_entry() #2 calls view_entry method
        elif choice == "3":
            break
        else:
            print("Pick 1–3.") #if user's input is invalid, print this

if __name__ == "__main__":
    main()
