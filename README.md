# eureka-project
i3blocks script and program to show upcoming eureka NMs on the i3bar

# set-up
download repo using `git clone`

compile the binary with `cd eureka-project` `make`

copy or link script file into i3blocks config directory

`cp eureka-project/i3blocks-script ~/.config/i3blocks/eureka`

`ln -s ~/Code/C++/eureka-project/i3blocks-script ~/.config/i3blocks/eureka`

confirm the `$BIN` var in the copied script points to the binary file
`BIN=~/Code/C++/eureka-project/bin`
modify `~/.config/i3blocks/config` by adding the following (use whatever interval you like)
```
[eureka]
interval=1
```
