# Setup
`git clone` inside your i3blocks `$SCRIPT_DIR` and build the project with make:
```
cd eureka-project
make
```

copy the contents of [i3blocks.conf](i3blocks.conf) into your config file
```
[eureka]
command=$SCRIPT_DIR/eureka-project/script
interval=1
```

if you decided to clone to a different directory, ensure that both 
[script](script) `WD=$SCRIPT_DIR/eureka-project` and 
[i3blocks.conf](i3blocks.conf) `command=$SCRIPT_DIR/eureka-project/script` 
reflect the correct locations
