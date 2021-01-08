# Creating coverage reports using meson

```
> meson -Db_coverage=true builddir && cd builddir
> ninja test
> ninja coverage-{text,xml}
```
* provided by [Gcovr](http://gcovr.com/) (version 3.3 or higher) 
* files at `./meson-logs/`

```
ninja coverage-html
```
* requires [Lcov](https://ltp.sourceforge.io/coverage/lcov.php) and [GenHTML](https://linux.die.net/man/1/genhtml) or [Gcovr](http://gcovr.com/). 
* files at `./meson-logs/coveragereport`

```
ninja coverage 
```
*   generates all three {text,xml, html}
  
https://mesonbuild.com/Unit-tests.html#coverage