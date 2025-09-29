# About
Display upcoming Eureka NMs in i3blocks with the following format:

![Skoll](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Skoll.png)

![Cassie](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Cassie.png)

> - name
> - time until weather condition opens
> - worst cast NM downtime (start of upcoming window - end of previous window)
> - *expected NM downtime (start of upcoming window - start of previous window)
> - *best case NM downtime (end of upcoming window - start of previous window)

*Some downtime entries will be omitted if earlier values already exceed the maximum cooldown duration of 120m.

![Pazuzu](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Pazuzu.png)

![ArthroPenny](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/ArthroPenny.png)

# Setup
`git clone` inside your i3blocks `$SCRIPT_DIR` and build the project with make: 
(The resulting `eureka` binary is placed in `eureka-project/..`)
```
cd eureka-project
make
```

Copy and paste the recommended [configuration](i3blocks.conf)
```
[eureka]
interval=persist
markup=pango
```

# Notes
After building the binary and copying the config, 
you can delete the git repo to save on disk space.

If you clone the project outside of the `$SCRIPT_DIR`, ensure to either:
- move the `eureka` binary to your `$SCRIPT_DIR`, or
- specify the alternate location with `command=/path/to/binary`
