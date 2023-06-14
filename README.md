# SSH-Wallet-Scammer
A simple "SSH Bitcoin wallet" program for learning purposes.

But there is no such thing as an SSH Bitcoin wallet.

The idea is to trick someone into thinking you leaked credentials for your supposed wallet.
He will then believe he gained the ability to withdraw bitcoin from it.
After that, the target will try to withdraw and will be told that the withdrawal address is not registered for the account.
He will then be told he needs to send 1 mBTC from the withdrawal address to the deposit address to confirm/register the former.

I found this scam on pastebin and recreated the program.
See further down how to bind the program to an SSH server properly.

Skipping over the menu options (see screenshots),
this program checks the environment variables for the username and logs all user input in a file.

## Building
Written in C, for unix systems.
Use the makefile !
Dependencies are the readline library, termcap library, curl and libbsd
It's basic C libs it should be installed already otherwise google it

See the header file to change certain things such as the BTC address, log file, or scam amount.

## Screenshots
![bob1](https://github.com/lopayet/SSH-Wallet-Scammer/assets/88368960/50904b59-a263-4be7-adac-99a9c564fd4e)
![bob2](https://github.com/lopayet/SSH-Wallet-Scammer/assets/88368960/24fe40c5-e63e-494b-9a32-1c486ccc82b0)
![bob3](https://github.com/lopayet/SSH-Wallet-Scammer/assets/88368960/d22a2044-d030-445f-a77c-0ca4d32a57b2)
![bob4](https://github.com/lopayet/SSH-Wallet-Scammer/assets/88368960/fad93dda-332f-4f08-8901-d4d6991020d2)

## Binding on SSH server
Assuming hypothetically the scam is run on a linux computer or VM,
you'd need to edit /etc/passwd for a certain user and edit such a line:
bobx1001:1001::/home/bob:/bin/bash
to
bobx1001:1001::/home/bob:/bin/wshell
hence replacing the shell used upon logging in the user (ssh or not).

You'd also need to place an empty file named exactly ".hushlogin" in the home directory of the user.
/home/bob/.hushlogin
to not receive any login message from the system upon connecting via ssh.

Finally you'd need to add a file named .inputrc in the home directory as well
/home/bob/.inputrc
and put this inside:
set disable-completion on
This is to disable auto completion when pressing tab, which would reveal all files in the working directory and break immersion.
