# Vex VScode extension deobfoscation

IF A CHANGE IS MADE IT MUST GO IN THIS FILE

### Changes made to origonal file:

* Formatted
* Almost every string was broken with the ending quote being on the next line and extra spaces added
* In the prosess of making some varible names uncryptic

### Function Signatures Changed:

* `async downloadSDK(t, e, o, s)` -> `async downloadSDK(platform, language, version, path)`
* `async _getManifestVersionOnline(t, e)` -> `async _getManifestVersionOnline(platform, language)`
* `oi = (_, t)` -> `normal_manifest_url = (platform, language)`
* `er = (_, t` -> `dev_manifest_url = (platform, language)`
* `Zi = (_, t)` -> `sdk_url = (platform, language)`
* `ms = (_)` -> `platform_url = (platform)`

### Variables Renamed:

* `Io` -> `normal_manifest`
* `Yi` -> `dev_manifest`
* `downloadSDK:n` -> `downloadSDK:save_path`
* `ps` -> `catalog`
* `tt` -> `request_responses`
* `ri` -> `platform_toolchains`
* `ot` -> `os`
* `be` -> `fs`
* `Zt` -> `https`
* `M` -> `vscode`
* `ni` -> `tar`
* `Oo` -> `unzipper`
* `ai` -> `etl`
* `Se` -> `path`
* `dt` -> `util`
* `Lo` -> `child_process`
* `ci` -> `tls`
* `Ee` -> `vscode`
* `li` -> `path`
* `vi` -> `vscode`
* `st` -> `vscode`
* `Jt` -> `vscode`
* `rt` -> `fs`
* `Mt` -> `child_process`
* `nt` -> `path`
* `is` -> `os`
* `oe` -> `vscode`
* `at` -> `os`

### Notes:

* The multiple reimports of dependencies are an effect of multiple files being combined durning the obfoscation prosess
