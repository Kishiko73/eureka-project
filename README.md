# About
Display upcoming Eureka NMs for FFXIV in i3blocks as a convenient heads up form of the 
[Eureka Tracker](https://ffxiv-eureka.com/local-tracker)

### Format
![Skoll](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Skoll.png)
![Cassie](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Cassie.png)
> ```
> - name
> - time until weather condition opens
> - worst cast NM downtime [m] (start of upcoming window -   end of previous window)
> - *expected  NM downtime [m] (start of upcoming window - start of previous window)
> - *best case NM downtime [m] (  end of upcoming window - start of previous window)
> ```
(*some downtime entries will be omitted if earlier values already exceed the maximum cooldown duration of 120m)

![Pazuzu](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/Pazuzu.png)
![ArthroPenny](https://github.com/Kishiko73/eureka-project/blob/master/screenshots/ArthroPenny.png)

**Tracked NMs**: Skoll, Copycat Cassie (Cassie), King Arthro (Arthro), Penthesilea (Penny), Pazuzu
 * Because Arthro and Penny weather windows perfectly overlap, they will always be listed together
 * In cases where Skoll and Pazuzu have overlapping weathers, Skoll is prioritized

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
### Notes
After building the binary and copying the config, you may delete the git repo to save on disk space.

If you clone the project outside of the `$SCRIPT_DIR`, ensure to either:
- move the `eureka` binary to your `$SCRIPT_DIR`, or
- specify the alternate location with `command=/path/to/binary`
