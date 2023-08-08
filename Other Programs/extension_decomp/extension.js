var yi = Object.create;
var jo = Object.defineProperty;
var Si = Object.getOwnPropertyDescriptor;
var Ei = Object.getOwnPropertyNames;
var Vi = Object.getPrototypeOf,
  Ti = Object.prototype.hasOwnProperty;
var ji = (_, t) => {
    for (var e in t)
      jo(_, e, {
        get: t[e],
        enumerable: !0,
      });
  },
  Ss = (_, t, e, o) => {
    if ((t && typeof t == "object") || typeof t == "function")
      for (let s of Ei(t))
        !Ti.call(_, s) &&
          s !== e &&
          jo(_, s, {
            get: () => t[s],
            enumerable: !(o = Si(t, s)) || o.enumerable,
          });
    return _;
  };
var L = (_, t, e) => (
    (e = _ != null ? yi(Vi(_)) : {}),
    Ss(
      t || !_ || !_.__esModule
        ? jo(e, "default", {
            value: _,
            enumerable: !0,
          })
        : e,
      _
    )
  ),
  Ri = (_) =>
    Ss(
      jo({}, "__esModule", {
        value: !0,
      }),
      _
    );
var ur = {};
ji(ur, {
  activate: () => pr,
  deactivate: () => mr,
});
module.exports = Ri(ur);
var vi = L(require("vscode"));
var st = L(require("vscode"));
var Jt = L(require("vscode"));
var rt = L(require("fs")),
  Mt = L(require("child_process")),
  nt = L(require("path")),
  is = L(require("os")),
  ki = "1.0.5",
  x = class {
    constructor(t, e, o) {
      (this._exeName = nt.basename(t)),
        (this._exePath = t),
        (this._exeParentPath = nt.dirname(t)),
        (this._devPath = e || ""),
        (this._queOptions = o || {
          active: !0,
          maxCmds: 0,
        }),
        this._checkFilePermissions();
    }
    vmDownload(t) {
      let e = "";
      if (t) {
        e = `--progress --python="${t}" ${this._devPath}`;
        let o = this.checkFile(t, e, x.CommandID.downloadPythonVM);
        if (o.exitCode !== x.ExitCode.vexSucess) return o;
      } else e = "--progress --python";
      return this._runVexcomCMD(e, x.CommandID.downloadPythonVM);
    }
    recoverFromDFU(t) {
      let e = "";
      return (
        (e = `--json --dfu=${t.toLowerCase()}`),
        this._runVexcomCMD(e, x.CommandID.recoverDFU)
      );
    }
    sytemUpdate(t, e = !1) {
      let o = "";
      e
        ? (o = `--quiet --progress --json --vexos-full --vexos "${t}" ${this._devPath}`)
        : (o = `--quiet --progress --json --vexos "${t}" ${this._devPath}`);
      let s = this.checkFile(t, o, x.CommandID.systemUpdate);
      return s.exitCode !== x.ExitCode.vexSucess
        ? new Promise((n) => n(s))
        : this._runVexcomCMD(o, x.CommandID.systemUpdate);
    }
    systemInfo() {
      let t = `--json ${this._devPath}`;
      return this._runVexcomCMD(t, x.CommandID.systemInfo);
    }
    controllerRadioFirmwareUpdate(t, e = !1) {
      let o = "";
      e
        ? (o = `--progress --json --ctrl-fw "${t}" ${this._devPath}`)
        : (o = `--progress --json --ctrl-fw "${t}" ${this._devPath}`);
      let s = this.checkFile(t, o, x.CommandID.controllerRadioUpdate);
      return s.exitCode !== x.ExitCode.vexSucess
        ? new Promise((n) => n(s))
        : this._runVexcomCMD(o, x.CommandID.controllerRadioUpdate);
    }
    controllerAtmelFirmwareUpdate(t) {
      let e = "";
      e = `--progress --json --atmel-fw "${t}" ${this._devPath}`;
      let o = this.checkFile(t, e, x.CommandID.controllerUsbUpdate);
      return o.exitCode !== x.ExitCode.vexSucess
        ? new Promise((s) => s(o))
        : this._runVexcomCMD(e, x.CommandID.controllerUsbUpdate);
    }
    systemStatus() {
      let t = `--status ${this._devPath}`;
      return this._runVexcomCMD(t, x.CommandID.systemStatus);
    }
    downloadUserProgram(
      t,
      e,
      o,
      s = x.SLOT.slot1,
      n = !1,
      a = !1,
      r = x.DownloadChannel.vexNoChannel
    ) {
      let c = "";
      n
        ? (c = ` --name "${t}" --slot ${s} --write "${o}" --progress --json --run`)
        : (c = ` --name "${t}" --slot ${s} --write "${o}" --progress --json`),
        (c += ` ${r}`),
        a && (c += " --progress"),
        e &&
          (c += ` --description ${Buffer.from(e, "binary").toString(
            "base64"
          )}`),
        (c += ` ${this._devPath}`);
      let l = this.checkFile(o, c, x.CommandID.downloadUserProgram);
      return l.exitCode !== x.ExitCode.vexSucess
        ? new Promise((d) => d(l))
        : this._runVexcomCMD(c, x.CommandID.downloadUserProgram);
    }
    eraseUserProgram(t) {
      let e = `--erase "${t}" ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.erase);
    }
    downloadPythonVM(t) {
      let e;
      if (t) {
        e = `${this._devPath} --python="${t}" --json --progress`;
        let o = this.checkFile(t, e, x.CommandID.downloadPythonVM);
        if (o.exitCode !== x.ExitCode.vexSucess)
          return new Promise((s) => s(o));
      } else e = `${this._devPath} --python --json --progress`;
      return this._runVexcomCMD(e, x.CommandID.downloadPythonVM);
    }
    stop() {
      let t = `--stop ${this._devPath}`;
      return this._runVexcomCMD(t, x.CommandID.stop);
    }
    play(t = x.SLOT.slot1) {
      let e = `--slot ${t} --run ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.play);
    }
    screenGrab(t) {
      let e = `--screen "${t}" ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.screenGrab);
    }
    batteryMedic() {
      let t = `--medic ${this._devPath}`;
      return this._runVexcomCMD(t, x.CommandID.batteryMedic);
    }
    setRobotName(t) {
      let e = `--robot "${t}" ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.setName);
    }
    setTeamNumber(t) {
      let e = `--team "${t}" ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.setTeam);
    }
    uploadEventLog(t = 1e3) {
      let e = `--eventlog ${t} --progress --json ${this._devPath}`;
      return this._runVexcomCMD(e, x.CommandID.uploadEventLog);
    }
    openUserPort(t) {
      let e = `--quiet --user ${t}`;
      return this._runVexcomUserCMD(e, x.CommandID.userPort);
    }
    listUSB(t) {
      let e = "--usb",
        o = !!t;
      return this._runVexcomCMD(e, x.CommandID.listUSB, o, t);
    }
    custom(t) {
      return this._runVexcomCMD(t, x.CommandID.custom);
    }
    getVersion() {
      let t = "--version --json";
      return this._runVexcomCMD(t, x.CommandID.vexcomVersion);
    }
    apiVersion() {
      return ki;
    }
    static getErrorCodeDetails(t) {
      return Es.get(t) ? Es.get(t) : `(${t}) Unknown Error Code`;
    }
    checkFile(t, e, o) {
      let s = {
        cmdID: o,
        cmdStr: `${nt.basename(this._exeParentPath)} ${e}`,
        stderr: "",
        stdout: "",
        exitCode: x.ExitCode.vexSucess,
      };
      if (!rt.existsSync(t))
        return (s.exitCode = x.ExitCode.vexAPIErrorFilePath), s;
      let a = [];
      switch (o) {
        case x.CommandID.downloadPythonVM:
          a = ["bin"];
          break;
        case x.CommandID.downloadUserProgram:
          a = ["bin", "py"];
          break;
        case x.CommandID.systemUpdate:
          a = ["vexos"];
          break;
        case x.CommandID.controllerRadioUpdate:
        case x.CommandID.controllerUsbUpdate:
          a = ["vexos"];
          break;
        default:
          a = [];
          break;
      }
      let r = nt.basename(t).split("."),
        c = r[r.length - 1];
      return (
        a.includes(c) || (s.exitCode = x.ExitCode.vexAPIErrorFileExtension), s
      );
    }
    _checkFilePermissions() {
      if (is.type() === "Linux") {
        let t = rt.statSync(this._exePath);
        (t.mode & 4095) !== 493 &&
          (console.log(
            "CHMOD",
            new TextDecoder().decode(
              Mt.spawnSync(`chmod 755 ${this._exePath}`, {
                shell: !0,
              }).stderr
            )
          ),
          (t = rt.statSync(this._exePath)),
          console.log("New File Permission", (t.mode & 4095).toString(8)));
      } else if (is.type() === "Darwin") {
        let t = nt.dirname(this._exePath),
          e = rt.readdirSync(t),
          o = [];
        o.push(this._exePath),
          o.forEach((s) => {
            let n = rt.statSync(s);
            (n.mode & 4095) !== 493 &&
              (console.log(
                "CHMOD",
                new TextDecoder().decode(
                  Mt.spawnSync(`chmod 755 ${this._exePath}`, {
                    shell: !0,
                  }).stderr
                )
              ),
              (n = rt.statSync(this._exePath)),
              console.log(
                `${nt.basename(s)}: Updated File Permission`,
                (n.mode & 4095).toString(8)
              ));
          });
      } else {
        let t = rt.statSync(this._exePath);
        (t.mode & 4095) !== 438 &&
          (console.log(
            "CHMOD",
            new TextDecoder().decode(
              Mt.spawnSync(`chmod +x ${this._exePath}`, {
                shell: !0,
              }).stderr
            )
          ),
          (t = rt.statSync(this._exePath)),
          console.log("New File Permission", (t.mode & 4095).toString(8)));
      }
    }
    _splitArgString(t) {
      let e = [];
      return (
        t.split(/\s/).forEach((o) => {
          (o !== "" || o !== "") && e.push(o);
        }),
        e
      );
    }
    _runVexcomCMD(t, e = x.CommandID.unknown, o = !1, s = void 0) {
      let n = this,
        a = this._exeParentPath;
      if (!rt.existsSync(this._exeParentPath)) {
        this._onErrorRecieved(
          e,
          Number(
            `${x.getErrorCodeDetails(x.ExitCode.vexAPIVexcomMissing)} ${a}`
          ),
          n
        ),
          this._onExitRecieved(e, x.ExitCode.vexAPIVexcomMissing, n);
        let c = {
          cmdID: e,
          cmdStr: `${this._exeName} ${t}`,
          stderr: "",
          stdout: "",
          exitCode: x.ExitCode.vexAPIVexcomMissing,
        };
        return new Promise((l) => {
          l(c);
        });
      }
      let r = (c, l) => {
        let d = e,
          m = `${this._exeName} ${t}`,
          w,
          b = "",
          C = "",
          E = !1,
          T = {};
        (T.cwd = this._exeParentPath),
          (T.PATH = this._exeParentPath + nt.delimiter + process.env.PATH);
        let O = {
          cwd: this._exeParentPath,
          shell: !0,
          env: T,
        };
        o
          ? (n._vexcomCP = Mt.spawn(
              "echo",
              this._splitArgString(`"${s}" | sudo -S ${this._exeName} ${t}`),
              O
            ))
          : (n._vexcomCP = Mt.spawn(this._exeName, this._splitArgString(t), O)),
          n._vexcomCP.stdout.on("data", function (f) {
            (C += f), n._onDataRecieved(d, f, n);
          }),
          n._vexcomCP.stderr.on("data", function (f) {
            (b += new TextDecoder().decode(f)), n._onErrorRecieved(d, f, n);
          }),
          n._vexcomCP.on("exit", function (f) {
            d === x.CommandID.systemInfo &&
              console.log(`ON EXIT - exit code: ${f}
`),
              (w = setTimeout(() => {
                let k = {
                  cmdID: d,
                  cmdStr: m,
                  stderr: b,
                  stdout: C,
                  exitCode: x.ExitCode.vexCMDTimeoutNoCloseEventRecieved,
                };
                c(k);
              }, 2e3));
          }),
          n._vexcomCP.on("close", function (f) {
            clearTimeout(w),
              d === x.CommandID.systemInfo &&
                console.log(`ON Close - exit code: ${f}
`),
              n._onExitRecieved(d, f, n),
              c({
                cmdID: d,
                cmdStr: m,
                stderr: b,
                stdout: C,
                exitCode: f,
              });
          });
      };
      return this._queOptions.active
        ? ut.enqueue(() => new Promise((c, l) => r(c, l)), e, t)
        : new Promise((c, l) => r(c, l));
    }
    _runVexcomUserCMD(t, e = x.CommandID.unknown) {
      let o = this;
      o._vexcomUserCP = void 0;
      let s = this._exePath;
      if (!rt.existsSync(this._exePath)) {
        this._onErrorRecieved(
          e,
          Number(
            `${x.getErrorCodeDetails(x.ExitCode.vexAPIVexcomMissing)} ${s}`
          ),
          o
        ),
          this._onExitRecieved(e, x.ExitCode.vexAPIVexcomMissing, o);
        let r = {
          cmdID: e,
          cmdStr: `${this._exeName} ${t}`,
          stderr: "",
          stdout: "",
          exitCode: x.ExitCode.vexAPIVexcomMissing,
        };
        return [
          void 0,
          new Promise((c) => {
            c(r);
          }),
        ];
      }
      let n = (r, c, l) => {
          let d = {};
          (d.cwd = this._exeParentPath),
            (d.PATH = this._exeParentPath + nt.delimiter + process.env.PATH);
          let m = {
              cwd: this._exeParentPath,
              shell: !0,
              env: d,
            },
            w = Mt.spawn(this._exeName, this._splitArgString(t), m);
          r(w);
        },
        a = async (r, c, l, d) => {
          let m = e,
            w = `${nt.basename(l._exePath)} ${t}`,
            b = "";
          (l._vexcomUserCP = await d),
            l._vexcomUserCP.stdout.on("data", function (C) {
              console.log(new TextDecoder().decode(C)),
                l._onUserDataRecieved(m, C, l);
            }),
            l._vexcomUserCP.stderr.on("data", function (C) {
              console.log(b),
                (b += new TextDecoder().decode(C)),
                l._onErrorRecieved(m, C, l);
            }),
            l._vexcomUserCP.on("exit", function (C) {
              l._onExitRecieved(m, C, l),
                r({
                  cmdID: m,
                  cmdStr: w,
                  stderr: b,
                  stdout: "",
                  exitCode: C,
                });
            });
        };
      if (this._queOptions.active) {
        let r,
          c = ut.enqueueGeneric(
            () => new Promise((d, m) => n(d, m, o)),
            x.CommandID.userPortCPStart
          ),
          l = ut.enqueue(() => new Promise((d, m) => a(d, m, o, c)), e, t);
        return [c, l];
      }
    }
    on(t, e) {
      switch (t) {
        case "UserRX":
          this.onUserRxFuncHandle = e;
          break;
        case "Data":
          this.onDataFuncHandle = e;
          break;
        case "Error":
          this.onErrorFuncHandle = e;
          break;
        case "Exit":
          this.onExitFuncHandle = e;
          break;
      }
    }
    _onUserDataRecieved(t, e, o) {
      o?.onUserRxFuncHandle && o.onUserRxFuncHandle(t, e);
    }
    _onDataRecieved(t, e, o) {
      o?.onDataFuncHandle && o?.onDataFuncHandle(t, e.toString());
    }
    _onErrorRecieved(t, e, o) {
      o?.onErrorFuncHandle &&
        o.onErrorFuncHandle(t, new TextDecoder().decode(e));
    }
    _onExitRecieved(t, e, o) {
      o?.onExitFuncHandle && o.onExitFuncHandle(t, e);
    }
    get activeCommand() {
      let t = {
        cmdID: x.CommandID.vexcom_doing_nothing,
        promiseFunc: () => {},
        reject: void 0,
        resolve: void 0,
      };
      return ut.activeCmd ? ut.activeCmd : t;
    }
  };
((s) => {
  let _;
  ((b) => (
    (b[(b.slot1 = 1)] = "slot1"),
    (b[(b.slot2 = 2)] = "slot2"),
    (b[(b.slot3 = 3)] = "slot3"),
    (b[(b.slot4 = 4)] = "slot4"),
    (b[(b.slot5 = 5)] = "slot5"),
    (b[(b.slot6 = 6)] = "slot6"),
    (b[(b.slot7 = 7)] = "slot7"),
    (b[(b.slot8 = 8)] = "slot8")
  ))((_ = s.SLOT || (s.SLOT = {})));
  let t;
  ((G) => (
    (G.vexcom_doing_nothing = "Doing nothing"),
    (G.unknown = "Unknown CMD"),
    (G.custom = "Custom CMD"),
    (G.play = "Play"),
    (G.stop = "Stop"),
    (G.erase = "Erase"),
    (G.downloadUserProgram = "User Program Download"),
    (G.downloadPythonVM = "Python VM Download"),
    (G.systemUpdate = "Vexos Update"),
    (G.controllerUsbUpdate = "Controller Usb Update"),
    (G.controllerRadioUpdate = "Controller Radio Update"),
    (G.recoverDFU = "Recover Brain in DFU Mode"),
    (G.batteryMedic = "Battery Medic"),
    (G.uploadEventLog = "Upload Event Log"),
    (G.setName = "Set Robot Name"),
    (G.setTeam = "Set Team Name"),
    (G.vexcomVersion = "Vexcom Version"),
    (G.systemInfo = "System Info"),
    (G.systemStatus = "System Status"),
    (G.listUSB = "List USB"),
    (G.screenGrab = "Screen Grab"),
    (G.userPortCPStart = "User Port - Start Child Process"),
    (G.userPort = "User Port - Result")
  ))((t = s.CommandID || (s.CommandID = {})));
  let e;
  ((X) => (
    (X[(X.vexCMDTimeoutNoCloseEventRecieved = -11)] =
      "vexCMDTimeoutNoCloseEventRecieved"),
    (X[(X.vexCMDTimeout = -10)] = "vexCMDTimeout"),
    (X[(X.vexCMDQueueSize = -9)] = "vexCMDQueueSize"),
    (X[(X.vexCMDQueueDownloadActive = -8)] = "vexCMDQueueDownloadActive"),
    (X[(X.vexAPIErrorOS = -7)] = "vexAPIErrorOS"),
    (X[(X.vexAPIErrorFileExtension = -6)] = "vexAPIErrorFileExtension"),
    (X[(X.vexAPIErrorFilePath = -5)] = "vexAPIErrorFilePath"),
    (X[(X.vexAPIVexcomAlive = -4)] = "vexAPIVexcomAlive"),
    (X[(X.vexAPIVexcomMissing = -3)] = "vexAPIVexcomMissing"),
    (X[(X.vexcomPlaceHolder2 = -2)] = "vexcomPlaceHolder2"),
    (X[(X.vexcomPlaceHolder1 = -1)] = "vexcomPlaceHolder1"),
    (X[(X.vexSucess = 0)] = "vexSucess"),
    (X[(X.vexError = 1)] = "vexError"),
    (X[(X.vexErrorAlive = 2)] = "vexErrorAlive"),
    (X[(X.vexErrorVersion = 3)] = "vexErrorVersion"),
    (X[(X.vexErrorCmd = 4)] = "vexErrorCmd"),
    (X[(X.vexErrorDevice = 5)] = "vexErrorDevice"),
    (X[(X.vexErrorPort = 6)] = "vexErrorPort"),
    (X[(X.vexErrorParam = 7)] = "vexErrorParam"),
    (X[(X.vexErrorVEXOS = 8)] = "vexErrorVEXOS")
  ))((e = s.ExitCode || (s.ExitCode = {})));
  let o;
  ((c) => (
    (c.vexNoChannel = ""),
    (c.vexPitChannel = "--chan 0 "),
    (c.vexDownloadchannel = "--chan 1 ")
  ))((o = s.DownloadChannel || (s.DownloadChannel = {})));
})(x || (x = {}));
var Es = new Map([
    [-11, "Vexcom command timeout, No Stdio closed event recieved"],
    [-10, "Vexcom command timeout, Vexcom Command killed"],
    [-9, "Max command queue limit reach, Vexcom Command Dropped"],
    [-8, "Vexcom Download Command in progress, Vexcom Command Dropped"],
    [-7, "Vexcom is not supported on this OS"],
    [-6, "Passed file extension is not supported"],
    [-5, "Passed file does not exist at directory"],
    [-4, "Vexcom alive message timeout"],
    [-3, "Vexcom Utillity is missing"],
    [0, "VEX Success"],
    [1, "VEX Error"],
    [2, "VEX Alive Error"],
    [3, "VEX Version Error"],
    [4, "VEX Command Error"],
    [5, "VEX Device Error"],
    [6, "VEX Port Error"],
    [7, "VEX Parameter Error"],
    [8, "VEX VEXOS Error"],
  ]),
  je = class {
    static setOptions(t) {
      je.options = t;
    }
    static enqueue(t, e, o) {
      return je.options.maxCmds && this.queue.length >= this.options.maxCmds
        ? new Promise((s) =>
            s({
              cmdID: e,
              cmdStr: o,
              stderr: "",
              stdout: "",
              exitCode: -9,
            })
          )
        : je?.activeCmd?.cmdID === "Vexos Update" ||
          je?.activeCmd?.cmdID === "User Program Download" ||
          je?.activeCmd?.cmdID === "Python VM Download" ||
          je?.activeCmd?.cmdID === "Controller Radio Update" ||
          je?.activeCmd?.cmdID === "Controller Usb Update"
        ? new Promise((s) =>
            s({
              cmdID: e,
              cmdStr: o,
              stderr: "",
              stdout: "",
              exitCode: -8,
            })
          )
        : new Promise((s, n) => {
            je.queue.push({
              promiseFunc: t,
              resolve: s,
              reject: n,
              cmdID: e,
            }),
              je.dequeue();
          });
    }
    static enqueueGeneric(t, e) {
      return new Promise((o, s) => {
        je.queue.push({
          promiseFunc: t,
          resolve: o,
          reject: s,
          cmdID: e,
        }),
          je.dequeue();
      });
    }
    static dequeue() {
      if (je.pendingPromise) return !1;
      let t = je.queue.shift();
      if (((je.activeCmd = t), !t)) return !1;
      try {
        (je.pendingPromise = !0),
          console.log(`Running Command: ${t.cmdID}`),
          t
            .promiseFunc(t.resolve, t.reject)
            .then((e) => {
              (je.pendingPromise = !1), t.resolve(e), je.dequeue();
            })
            .catch((e) => {
              (je.pendingPromise = !1), t.reject(e), je.dequeue();
            });
      } catch (e) {
        (je.pendingPromise = !1), t.reject(e), je.dequeue();
      }
      return !0;
    }
  },
  ut = je;
(ut.options = {
  active: !1,
  maxCmds: 0,
}),
  (ut.queue = []),
  (ut.pendingPromise = !1),
  (ut.activeCmd = {
    cmdID: "Doing nothing",
    promiseFunc: () => {},
    reject: void 0,
    resolve: void 0,
  });
var oe = L(require("vscode")),
  at = L(require("os")),
  ko = L(require("path")),
  ct = L(require("fs")),
  js = L(require("unzipper"));
var Vs = L(require("crypto")),
  fo = L(require("fs")),
  Ro = L(require("path"));
var F = class {
  constructor(t) {
    this._serialPort = t;
  }
  async restartTerminal() {
    let t;
    return (
      (t = await this._send3DAICMD(
        this.getRunCMD("systemctl restart serial-getty@ttyGS0.service", "") +
          `
`,
        F.Commands.run
      )),
      t
    );
  }
  clearRxBufferCMD() {
    let t = {
      command: F.Commands.clear,
    };
    return this._send3DAICMD(
      JSON.stringify(t) +
        `
`,
      F.Commands.clear
    );
  }
  sendAlive() {
    let t = {
      command: F.Commands.isAlive,
    };
    return this._send3DAICMD(
      JSON.stringify(t) +
        `
`,
      F.Commands.isAlive
    );
  }
  setAccessPointSSID(t) {
    let e = {
      command: F.Commands.setSSID,
      name: `${t}`,
    };
    return this._send3DAICMD(
      JSON.stringify(e) +
        `
`,
      F.Commands.setSSID
    );
  }
  setAccessPointPassword(t) {
    let e = {
      command: F.Commands.setPassword,
      password: t,
    };
    return this._send3DAICMD(
      JSON.stringify(e) +
        `
`,
      F.Commands.setPassword
    );
  }
  getDeviceInfo(t) {
    let e = {
      command: F.Commands.deviceInfo,
      appList: t || [],
    };
    return this._send3DAICMD(
      JSON.stringify(e) +
        `
`,
      F.Commands.deviceInfo
    );
  }
  getCheckElevateCMD() {
    let t = {
      command: F.Commands.checkElevate,
    };
    return this._send3DAICMD(
      JSON.stringify(t) +
        `
`,
      F.Commands.checkElevate
    );
  }
  getElevateCMD() {
    let t = {
      command: F.Commands.elevate,
    };
    return this._send3DAICMD(
      JSON.stringify(t) +
        `
`,
      F.Commands.elevate
    );
  }
  checkDirCMD(t) {
    let e = "",
      o = `[ -d "${t}" ]`;
    return this._send3DAICMD(
      this.getRunCMD(o, e) +
        `
`,
      F.Commands.run
    );
  }
  installAppCMD(t) {
    let e = "",
      o = `dpkg -i ${t}`;
    return this._send3DAICMD(
      this.getRunCMD(o, e) +
        `
`,
      F.Commands.run
    );
  }
  removeAppCMD(t) {
    let e = "",
      o = `dpkg -r ${t}`;
    return this._send3DAICMD(
      this.getRunCMD(o, e) +
        `
`,
      F.Commands.run
    );
  }
  restartServiceCMD(t, e) {
    let o = "",
      s = `systemctl ${e} ${t}`;
    return this._send3DAICMD(
      this.getRunCMD(s, o) +
        `
`,
      F.Commands.run
    );
  }
  rmCMD(t, e) {
    let o = e || "/",
      s = `rm ${t}`;
    return this._send3DAICMD(
      this.getRunCMD(s, o) +
        `
`,
      F.Commands.run
    );
  }
  async downloadApplication(t, e, o) {
    let s = Ro.basename(t),
      n = Ro.join("home", "root", s),
      a = e || n,
      r = this._getFileDataCMDStart(a.replace(/\\/gi, "/")),
      c = fo.statSync(t);
    var l = fo.createReadStream(t, {
        highWaterMark: 1024 * 32,
      }),
      d = fo.createReadStream(t, {
        highWaterMark: 1024 * 32,
      }),
      m = Vs.createHash("md5");
    d.pipe(m);
    let w = "";
    console.time("FileD"), await this._send3DAICMD(r, F.Commands.download, !0);
    let b = !1;
    l.on("data", (f) => {
      l.pause();
      let k = f.toString("base64");
      try {
        this._serialPort.write(k + ",", "utf-8", async (z) => {
          l.resume();
        });
      } catch {
        (b = !0), l.close(), l.destroy();
      }
    }),
      l.on("end", function () {
        l.close(), l.destroy();
      });
    let C = 0;
    for (; !l.destroyed; ) {
      let f = l.bytesRead - C;
      (C = l.bytesRead),
        await i.Utils.asyncSleep(100),
        console.timeLog("FileD", `${(l.bytesRead / c.size) * 100}%`),
        o({
          message: `${((l.bytesRead / c.size) * 100).toFixed(1)}%`,
          increment: (f / c.size) * 100,
        });
    }
    if (b)
      return {
        vexaicommsI: "",
        cmdID: F.Commands.download,
        cmdStr: "",
        data: new Uint8Array(),
        details: "",
        exitCode: F.StatusCodes.port_not_open,
      };
    let T = `${this._getFileDataCMDEnd(m.digest("hex"))}
`,
      O = `${r}${w}${T}`;
    return (
      console.log(JSON.parse(O)),
      console.timeLog("FileD", `${l.bytesRead}`),
      console.timeEnd("FileD"),
      o({
        message: "Writting File . . .",
        increment: -101,
      }),
      this._send3DAICMD(T, F.Commands.download)
    );
  }
  _getFileDataCMDStart(t) {
    let e = {
      command: F.Commands.download,
      filepath: t,
      filedata: "${placeHolder}",
      checksum: "",
    };
    return JSON.stringify(e).split("${placeHolder}")[0];
  }
  _getFileDataCMDEnd(t) {
    let e = {
      command: F.Commands.download,
      filepath: "",
      filedata: "${placeHolder}",
      checksum: t,
    };
    return JSON.stringify(e).split("${placeHolder}")[1];
  }
  getRunCMD(t, e) {
    let o = {
      command: F.Commands.run,
      args: t,
      path: e,
    };
    return JSON.stringify(o);
  }
  static getErrorResp(t, e) {
    let o = {
      command: t,
      error: e,
      response: F.getErrorCodeDetails(F.StatusCodes.nack),
    };
    return {
      vexaicommsI: "",
      cmdID: o.command,
      cmdStr: "",
      data: new TextEncoder().encode(JSON.stringify(o)),
      details: o.error,
      exitCode: F.StatusCodes.nack,
    };
  }
  async _send3DAICMD(t, e = F.Commands.unknown, o = !1) {
    let s = {
      vexaicommsI: "",
      cmdID: e,
      cmdStr: t,
      data: void 0,
      details: "",
      exitCode: F.StatusCodes.nack,
    };
    if (!this._serialPort.isOpen)
      return (s.exitCode = F.StatusCodes.port_not_open), s;
    let n = await gt.enqueue(() => {
      let a, r;
      return [
        new Promise((l, d) => {
          (a = l),
            (r = d),
            o
              ? this._serialPort.write(t, "utf-8", (m) => {
                  m ? d(new Uint8Array()) : l(new Uint8Array());
                })
              : this._serialPort.write(t, "utf-8", (m) => {
                  console.log(m);
                });
        }),
        a,
        r,
      ];
    }, e);
    return (n.cmdStr = s.cmdStr.replace(/\n/gi, "")), n;
  }
  static getErrorCodeDetails(t) {
    return F.vexaiErrorMap.get(t)
      ? F.vexaiErrorMap.get(t)
      : `(${t}) Unknown Error Code`;
  }
};
((o) => {
  let _;
  ((f) => (
    (f.clear = "clear"),
    (f.updateVersion = "update_version"),
    (f.appVersion = "app_version"),
    (f.webVersion = "web_version"),
    (f.deviceInfo = "device_info"),
    (f.isAlive = "alive"),
    (f.elevate = "elevate"),
    (f.checkElevate = "check_elevate"),
    (f.setSSID = "set_ap_name"),
    (f.setPassword = "set_ap_password"),
    (f.run = "run"),
    (f.download = "download"),
    (f.doing_nothing = "doing nothing"),
    (f.unknown = "unknown command")
  ))((_ = o.Commands || (o.Commands = {})));
  let t;
  ((b) => (
    (b[(b.unknownResp = -100)] = "unknownResp"),
    (b[(b.deviceNotAlive = -7)] = "deviceNotAlive"),
    (b[(b.vexupdateMissing = -6)] = "vexupdateMissing"),
    (b[(b.clear = -5)] = "clear"),
    (b[(b.downloadCommandActive = -4)] = "downloadCommandActive"),
    (b[(b.port_not_open = -3)] = "port_not_open"),
    (b[(b.timeout = -2)] = "timeout"),
    (b[(b.nack = -1)] = "nack"),
    (b[(b.ack = 0)] = "ack")
  ))((t = o.StatusCodes || (o.StatusCodes = {}))),
    (o.vexaiErrorMap = new Map([
      [-100, "Command Response Not Recognized"],
      [-6, "Vexupdate is missing, can't send command"],
      [-7, "Device is not alive, can't send command"],
      [-5, "Clearing vexupdate command buffer"],
      [-4, "Command Dropped Download Command In Progress"],
      [-3, "Command Dropped Serial Port is not open"],
      [-2, "Command Timout Occurried"],
      [0, "ACK"],
      [-1, "NACK"],
    ]));
})(F || (F = {}));
var Ie = class {
    static setOptions(t) {
      Ie.options = t;
    }
    static enqueueGeneric(t, e) {
      return new Promise((o, s) => {
        Ie.queue.push({
          promiseFunc: t,
          externalResolve: o,
          externalReject: s,
          internalReject: void 0,
          internalResolve: void 0,
          cmdID: e,
        }),
          Ie.dequeue();
      });
    }
    static enqueue(t, e) {
      return Ie?.activeCmd?.cmdID === "download"
        ? new Promise((o) =>
            o({
              vexaicommsI: "",
              cmdID: e,
              cmdStr: "",
              data: new Uint8Array(),
              details: "",
              exitCode: -4,
            })
          )
        : new Promise((o, s) => {
            Ie.queue.push({
              promiseFunc: t,
              externalResolve: o,
              externalReject: s,
              internalReject: void 0,
              internalResolve: void 0,
              cmdID: e,
            }),
              Ie.dequeue();
          });
    }
    static dequeue() {
      if (Ie.pendingPromise) return !1;
      let t = Ie.queue.shift();
      if (((Ie.activeCmd = t), !t)) return !1;
      let e;
      console.time("Command"),
        Ie.activeCmd.cmdID === "device_info" &&
          (e = setTimeout(() => {
            let o = Ie.activeCmd.cmdID + "Timeout Occurried";
            Ie.activeCmd.internalResolve(F.getErrorResp(Ie.activeCmd.cmdID, o)),
              console.timeLog("Command", "Timeout Occurried");
          }, 3e3)),
        (Ie.activeCmd.cmdID === "alive" || Ie.activeCmd.cmdID === "clear") &&
          (e = setTimeout(() => {
            let o = Ie.activeCmd.cmdID + "Timeout Occurried";
            Ie.activeCmd.internalResolve(F.getErrorResp(Ie.activeCmd.cmdID, o)),
              console.timeLog("Command", "Timeout Occurried");
          }, 1e3));
      try {
        (Ie.pendingPromise = !0), console.log(`Running Command: ${t.cmdID}`);
        let o = t.promiseFunc();
        (Ie.activeCmd.internalResolve = o[1]),
          (Ie.activeCmd.internalReject = o[2]),
          o[0]
            .then((s) => {
              console.log(`Finished Command: ${t.cmdID} ${JSON.stringify(s)}`),
                (Ie.pendingPromise = !1),
                t.externalResolve(s),
                clearTimeout(e),
                console.timeLog("Command", "Timeout Cleared"),
                console.timeEnd("Command"),
                Ie.dequeue();
            })
            .catch((s) => {
              (Ie.pendingPromise = !1),
                t.externalReject(s),
                clearTimeout(e),
                Ie.dequeue();
            });
      } catch (o) {
        (Ie.pendingPromise = !1), t.externalReject(o), Ie.dequeue();
      }
      return !0;
    }
  },
  gt = Ie;
(gt.options = {
  active: !1,
  maxCmds: 0,
}),
  (gt.queue = []),
  (gt.pendingPromise = !1),
  (gt.activeCmd = {
    cmdID: "doing nothing",
    promiseFunc: () => {},
    internalReject: void 0,
    internalResolve: void 0,
    externalReject: void 0,
    externalResolve: void 0,
  });
var wt = L(require("fs")),
  Gt = L(require("child_process")),
  Ge = L(require("path")),
  rs = L(require("os")),
  Pe = class {
    constructor(t, e) {
      this.returnMsg = {
        messege: "",
        progress: 0,
      };
      (this._exeName = Ge.basename(t)),
        (this._exePath = t),
        (this._exeParentPath = Ge.dirname(t)),
        this._checkFilePermissions();
    }
    flash(t, e = 10, o) {
      let s = Ge.resolve(t, "_flash.bin"),
        n = Ge.resolve(t, "_image"),
        a = `-v -b emmc_all "${s}" "${n}" -t ${e}`,
        r = this.checkFile(`${s}`, a, Pe.CommandID.flashImage);
      if (r.exitCode !== Pe.ExitCode.uuuSuccess)
        return new Promise((l) => l(r));
      if (
        ((r = this.checkFile(`${n}`, a, Pe.CommandID.flashImage)),
        r.exitCode !== Pe.ExitCode.uuuSuccess)
      )
        return new Promise((l) => l(r));
      let c = !!o;
      return this._runUUUCMD(a, Pe.CommandID.flashImage, c, o);
    }
    flash_bootloader(t, e) {
      let o = Ge.resolve(t, "_flash.bin"),
        s = `-v -b emmc_all "${o}"`,
        n = this.checkFile(`${o}`, s, Pe.CommandID.flashImage);
      if (n.exitCode !== Pe.ExitCode.uuuSuccess)
        return new Promise((r) => r(n));
      let a = !!e;
      return this._runUUUCMD(s, Pe.CommandID.flashImage, a, e);
    }
    fb_command(t) {
      let e = `FB: ${t}`;
      return this._runUUUCMD(e, Pe.CommandID.unknown);
    }
    listDevices() {
      let t = "-lsusb";
      return this._runUUUCMD(t, Pe.CommandID.listUSB);
    }
    kill() {
      this._uuuCP.kill();
    }
    custom(t) {
      return this._runUUUCMD(t, Pe.CommandID.custom);
    }
    static getErrorCodeDetails(t) {
      return Ts.get(t) ? Ts.get(t) : `(${t}) Unknown Error Code`;
    }
    _checkFilePermissions() {
      if (rs.type() === "Linux") {
        let t = wt.statSync(this._exePath);
        (t.mode & 4095) !== 493 &&
          (console.log(
            "CHMOD",
            new TextDecoder().decode(
              Gt.spawnSync(`chmod 755 ${this._exePath}`, {
                shell: !0,
              }).stderr
            )
          ),
          (t = wt.statSync(this._exePath)),
          console.log("New File Permission", (t.mode & 4095).toString(8)));
      } else if (rs.type() === "Darwin") {
        let t = Ge.dirname(this._exePath),
          e = [];
        e.push(this._exePath),
          e.forEach((o) => {
            let s = wt.statSync(o);
            (s.mode & 4095) !== 493 &&
              (console.log(
                "CHMOD",
                new TextDecoder().decode(
                  Gt.spawnSync(`chmod 755 ${this._exePath}`, {
                    shell: !0,
                  }).stderr
                )
              ),
              (s = wt.statSync(this._exePath)),
              console.log(
                `${Ge.basename(o)}: Updated File Permission`,
                (s.mode & 4095).toString(8)
              ));
          });
      } else {
        let t = wt.statSync(this._exePath);
        (t.mode & 4095) !== 438 &&
          (console.log(
            "CHMOD",
            new TextDecoder().decode(
              Gt.spawnSync(`chmod +x ${this._exePath}`, {
                shell: !0,
              }).stderr
            )
          ),
          (t = wt.statSync(this._exePath)),
          console.log("New File Permission", (t.mode & 4095).toString(8)));
      }
    }
    _splitArgString(t) {
      let e = [];
      return (
        t.split(/\s/).forEach((o) => {
          (o !== "" || o !== "") && e.push(o);
        }),
        e
      );
    }
    _parseUUUOutput(t, e, o) {
      console.log(o);
      let s = {
          messege: "",
          progress: 0,
        },
        n = RegExp(/_flash\.bin/),
        a = RegExp(/_image/),
        r = RegExp(/_image/),
        c = RegExp(/[0-9]?[0-9]?[0-9]%/);
      return (
        a.test(o) && (this.returnMsg.messege = "Flashing Image"),
        n.test(o) && (this.returnMsg.messege = "Flashing Bootloader"),
        c.test(o) &&
          ((this.returnMsg.progress = Number(c.exec(o)[0].split("%")[0])),
          this._onProgressRecieved(e, this.returnMsg, o, t)),
        console.log(this.returnMsg),
        this.returnMsg
      );
    }
    _runUUUCMD(t, e = Pe.CommandID.unknown, o = !1, s = "") {
      let n = this,
        a = this._exeParentPath;
      if (!wt.existsSync(this._exeParentPath)) {
        this._onErrorRecieved(
          e,
          Number(`${Pe.getErrorCodeDetails(Pe.ExitCode.uuuAPIMissing)} ${a}`),
          n
        ),
          this._onExitRecieved(e, Pe.ExitCode.uuuAPIMissing, n);
        let c = {
          uuuI: "",
          cmdID: e,
          cmdStr: `${this._exeName} ${t}`,
          stderr: "",
          stdout: "",
          exitCode: Pe.ExitCode.uuuAPIMissing,
        };
        return new Promise((l) => {
          l(c);
        });
      }
      let r = (c, l) => {
        let d = e,
          m = o
            ? `echo "****" | sudo -S ${this._exeName} ${t}`
            : `${this._exeName} ${t}`,
          w = "",
          b = "",
          C = {};
        (C.cwd = this._exeParentPath),
          (C.PATH = this._exeParentPath + Ge.delimiter + process.env.PATH);
        let E = {
          cwd: this._exeParentPath,
          shell: !0,
          env: C,
        };
        o
          ? (n._uuuCP = Gt.spawn(
              "echo",
              this._splitArgString(`"${s}" | sudo -S ${this._exeName} ${t}`),
              E
            ))
          : (n._uuuCP = Gt.spawn(this._exeName, this._splitArgString(t), E)),
          n._uuuCP.stdout.on("data", function (T) {
            n._onDataRecieved(d, T, n),
              console.log(new TextDecoder().decode(T)),
              (b += T),
              n._parseUUUOutput(n, e, new TextDecoder().decode(T));
          }),
          n._uuuCP.stderr.on("data", function (T) {
            (w += new TextDecoder().decode(T)),
              console.log(new TextDecoder().decode(T)),
              n._onErrorRecieved(d, T, n);
          }),
          n._uuuCP.on("close", function (T) {
            let O = {
              uuuI: "",
              cmdID: d,
              cmdStr: m,
              stderr: w,
              stdout: b,
              exitCode: T,
            };
          }),
          n._uuuCP.on("exit", function (T) {
            n._onExitRecieved(d, T, n),
              c({
                uuuI: "",
                cmdID: d,
                cmdStr: m,
                stderr: w,
                stdout: b,
                exitCode: T,
              });
          });
      };
      return new Promise((c, l) => r(c, l));
    }
    on(t, e) {
      switch (t) {
        case "Data":
          this.onDataFuncHandle = e;
          break;
        case "Progress":
          this.onProgressFuncHandle = e;
          break;
        case "Error":
          this.onErrorFuncHandle = e;
          break;
        case "Exit":
          this.onExitFuncHandle = e;
          break;
      }
    }
    _onDataRecieved(t, e, o) {
      o?.onDataFuncHandle && o.onDataFuncHandle(t, e.toString());
    }
    _onProgressRecieved(t, e, o, s) {
      s?.onProgressFuncHandle && s.onProgressFuncHandle(t, e, o);
    }
    _onErrorRecieved(t, e, o) {
      o?.onErrorFuncHandle &&
        o.onErrorFuncHandle(t, new TextDecoder().decode(e));
    }
    _onExitRecieved(t, e, o) {
      o?.onExitFuncHandle && o.onExitFuncHandle(t, e);
    }
    checkFile(t, e, o) {
      let s = {
        uuuI: "",
        cmdID: o,
        cmdStr: `${Ge.basename(this._exeParentPath)} ${e}`,
        stderr: "",
        stdout: "",
        exitCode: Pe.ExitCode.uuuSuccess,
      };
      if (!wt.existsSync(t))
        return (s.exitCode = Pe.ExitCode.uuuAPIErrorFilePath), s;
      let a = [];
      switch (o) {
        case Pe.CommandID.flashImage:
          a = [".bin", ""];
          break;
        default:
          a = [];
          break;
      }
      let r = Ge.extname(t) ? Ge.extname(t) : "";
      return (
        a.includes(r) || (s.exitCode = Pe.ExitCode.uuuAPIErrorFileExtension), s
      );
    }
  };
((e) => {
  let _;
  ((c) => (
    (c.uuu_doing_nothing = "Doing Nothing"),
    (c.unknown = "Unknown Command"),
    (c.custom = "Custom Command"),
    (c.flashImage = "Flash Image"),
    (c.listUSB = "List USB Devices")
  ))((_ = e.CommandID || (e.CommandID = {})));
  let t;
  ((w) => (
    (w[(w.uuuError = -1)] = "uuuError"),
    (w[(w.uuuSuccess = 0)] = "uuuSuccess"),
    (w[(w.uuuAPIErrorOS = 1)] = "uuuAPIErrorOS"),
    (w[(w.uuuAPIMissing = 2)] = "uuuAPIMissing"),
    (w[(w.uuuAPIAlive = 3)] = "uuuAPIAlive"),
    (w[(w.uuuAPIErrorFileExtension = 4)] = "uuuAPIErrorFileExtension"),
    (w[(w.uuuAPIErrorFilePath = 5)] = "uuuAPIErrorFilePath"),
    (w[(w.uuuAPIVexcomAlive = 6)] = "uuuAPIVexcomAlive"),
    (w[(w.uuuAPIVexcomMissing = 7)] = "uuuAPIVexcomMissing")
  ))((t = e.ExitCode || (e.ExitCode = {})));
})(Pe || (Pe = {}));
var Ts = new Map([
  [-1, "Unknown UUU Error"],
  [0, "UUU Success"],
  [1, "UUU is not supported on this OS"],
  [2, "UUU utility is missing"],
  [3, "UUU is alive, timeout"],
]);
var Rs = L(require("crypto")),
  i;
((r) => {
  r.DEBUG = !0;
  let t;
  ((b) => (
    (b.Brain = "Brain"),
    (b.Camera_2D = "2 D Camera"),
    (b.Camera_3D = "3 D Camera"),
    (b.Controller = "Controller"),
    (b.Unknown = "unknown")
  ))((t = r.Device || (r.Device = {})));
  let e;
  ((b) => (
    (b.AI = "AI"),
    (b.V5 = "V5"),
    (b.EXP = "EXP"),
    (b.IQ2 = "IQ2"),
    (b.Unknown = "unknown")
  ))((e = r.Platform || (r.Platform = {})));
  let o;
  ((m) => ((m.cpp = "cpp"), (m.python = "python"), (m.unknown = "unknown")))(
    (o = r.Language || (r.Language = {}))
  );
  let s;
  ((S) => {
    (S.name = "vexcode"),
      (S.author = "vexrobotics"),
      (S.id = `${S.author}.${S.name}`);
    function w() {
      return oe.extensions.all.filter((V) => V.id.includes(S.name))[0]
        .packageJSON.version;
    }
    (S.version = w), (S.vexcomVersion = "");
    function C(W) {
      let V;
      return (
        at.type() === "Windows_NT" &&
          (V = oe.Uri.joinPath(
            W.extensionUri,
            "resources",
            "tools",
            "vexcom",
            "win32",
            "vexcom.exe"
          )),
        at.type() === "Darwin" &&
          (V = oe.Uri.joinPath(
            W.extensionUri,
            "resources",
            "tools",
            "vexcom",
            "osx",
            "vexcom"
          )),
        at.type() === "Linux" &&
          at.arch() === "x64" &&
          (V = oe.Uri.joinPath(
            W.extensionUri,
            "resources",
            "tools",
            "vexcom",
            "linux-x64",
            "vexcom"
          )),
        at.type() === "Linux" &&
          at.arch() === "arm64" &&
          (V = oe.Uri.joinPath(
            W.extensionUri,
            "resources",
            "tools",
            "vexcom",
            "linux-arm64",
            "vexcom"
          )),
        at.type() === "Linux" &&
          at.arch() === "arm" &&
          (V = oe.Uri.joinPath(
            W.extensionUri,
            "resources",
            "tools",
            "vexcom",
            "linux-arm32",
            "vexcom"
          )),
        V
      );
    }
    S.getVexcomUri = C;
    let E = new Map([
      ["vexlog.error", "#ff3232"],
      ["vexlog.warning", "#FFFF00"],
      ["vexlog.normal", "#4479ff"],
      ["vexlog.battery", "# 4479 ff "],
      ["vexlog.power", "#00a000"],
    ]);
    async function T() {
      let W = [
          {
            scope: "vexlog.error",
            foreground: "#ff3232",
          },
          {
            scope: "vexlog.warning",
            foreground: "#FFFF00",
          },
          {
            scope: "vexlog.normal",
            foreground: "#4479ff",
          },
          {
            scope: "vexlog.battery",
            foreground: "#4479ff",
          },
          {
            scope: "vexlog.power",
            foreground: "#00a000",
          },
        ],
        V = oe.workspace
          .getConfiguration()
          .get("editor.tokenColorCustomizations.textMateRules"),
        X = [];
      W.forEach((se) => {
        V.some(
          (re) =>
            re.scope === se.scope && re.settings.foreground === se.foreground
        ) ||
          X.push({
            scope: se.scope,
            settings: {
              foreground: se.foreground,
            },
          });
      }),
        X.forEach((se) => V.push(se)),
        await oe.workspace.getConfiguration().update(
          "editor.tokenColorCustomizations",
          {
            textMateRules: V,
          },
          oe.ConfigurationTarget.Global,
          !0
        ),
        console.log("done");
    }
    S.setVexlogColor = T;
    let O;
    ((re) => {
      (re.vexProjectSettingsFolderArrID = `${S.id}.vexProjectSettingsFolderArr`),
        (re.isValidProjectID = `${S.id}.isValidProjectID`),
        (re.debugEnabled = `${S.id}.debugEnabled`),
        (re.isDevEnabled = !1);
      async function se(fe) {
        return oe.commands.executeCommand(
          "setContext",
          re.isValidProjectID,
          fe
        );
      }
      re.setIsValidProject = se;
      async function G(fe) {
        return (
          (re.isDevEnabled = fe),
          oe.commands.executeCommand("setContext", re.debugEnabled, fe)
        );
      }
      re.setDebug = G;
    })((O = S.Context || (S.Context = {})));
    let f;
    ((Q) => {
      (Q.buildID = `${S.id}.project.build`),
        (Q.cleanID = `${S.id}.project.clean`),
        (Q.rebuildID = `${S.id}.project.rebuild`),
        (Q.newProjectID = `${S.id}.project.new`),
        (Q.importID = `${S.id}.project.import`),
        (Q.settingUIID = `${S.id}.project.settingsUI`),
        (Q.eraseID = `${S.id}.system.erase`),
        (Q.downloadID = `${S.id}.system.download`),
        (Q.systemInfoID = `${S.id}.system.info`),
        (Q.screenGrabID = `${S.id}.system.screen-grab`),
        (Q.brainNameID = `${S.id}.system.brain-name`),
        (Q.teamNumberID = `${S.id}.system.team-number`),
        (Q.batteryMedicID = `${S.id}.system.battery-medic`),
        (Q.systemUpdateVEXosID = `${S.id}.system.update.vexos`),
        (Q.systemUpdatePythonVmID = `${S.id}.system.update.pythonVM`),
        (Q.controllerUpdateFirmwareID = `${S.id}.system.update.controller`),
        (Q.dfuUpdateFirmwareID = `${S.id}.system.update.dfu`),
        (Q.uploadEventLogID = `${S.id}.system.uploadEventLog`),
        (Q.update3dAICameraImage = `${S.id}.camera.3d.image.update`),
        (Q.flashAICamera = `${S.id}.camera.3d.flash`),
        (Q.set3DSSID = `${S.id}.camera.3d.set-ssid`),
        (Q.set3DPassword = `${S.id}.camera.3d.set-password`),
        (Q.download3DApp = `${S.id}.camera.3d.app.update`),
        (Q.reset3DUserTerminal = `${S.id}.camera.3d.resetTerminal`),
        (Q.vexCommandHelpID = `${S.id}.command-help`),
        (Q.vexCommandHelpShowAllID = `${S.id}.command-help.show-all`),
        (Q.downloadSDKID = `${S.id}.resourceManager.download.sdk`),
        (Q.downloadToolchainID = `${S.id}.resourceManager.download.toolchain`),
        (Q.clearLogTerminalID = `${S.id}.terminal.log.clear`),
        (Q.clearInterativeTerminalID = `${S.id}.terminal.interactive.clear`),
        (Q.createNewTerminalSetID = `${S.id}.terminal.newset`),
        (Q.TEST_COMMAND = `${S.id}.test`),
        (Q.systemRecoverID = `${S.id}.system.recover`),
        (Q.installDrivers = `${S.id}.drivers.install`),
        (Q.controllerUpdateFirmwareAtmelID = `${S.id}.system.update.controller.atmel`),
        (Q.controllerUpdateFirmwareRadioDEVID = `${S.id}.system.update.controller.radio`),
        (Q.controllerUpdateFirmwareDEVID = `${S.id}.system.update.controllerMenu`),
        (Q.brainUpdateFirmwareDEVID = `${S.id}.system.update.brainMenu`),
        (Q.webSocketSettings = `${S.id}.websocket.settings`),
        (Q.downloadAI = `${S.id}.ai.downloadfile`);
      async function ws() {
        return oe.commands.executeCommand(Q.buildID);
      }
      Q.build = ws;
      async function Cs() {
        return oe.commands.executeCommand(Q.cleanID);
      }
      Q.clean = Cs;
      async function fi() {
        return oe.commands.executeCommand(Q.rebuildID);
      }
      Q.rebuild = fi;
      async function Zo() {
        return oe.commands.executeCommand(Q.newProjectID);
      }
      Q.newProject = Zo;
      async function mo() {
        return oe.commands.executeCommand(Q.importID);
      }
      Q.importProject = mo;
      async function Eo() {
        return oe.commands.executeCommand(Q.systemInfoID);
      }
      Q.systemInfo = Eo;
      async function $t() {
        return oe.commands.executeCommand(Q.screenGrabID);
      }
      Q.screenGrab = $t;
      async function es() {
        return oe.commands.executeCommand(Q.brainNameID);
      }
      Q.setBrainName = es;
      async function hi() {
        return oe.commands.executeCommand(Q.teamNumberID);
      }
      Q.setTeamNumber = hi;
      async function xi() {
        return oe.commands.executeCommand(Q.batteryMedicID);
      }
      Q.batteryMedic = xi;
      async function Is() {
        return oe.commands.executeCommand(Q.systemUpdateVEXosID);
      }
      Q.systemUpdateVEXos = Is;
      async function ts(os) {
        return oe.commands.executeCommand(Q.systemUpdatePythonVmID, os);
      }
      Q.systemUpdatePythonVM = ts;
      async function Ps() {
        return oe.commands.executeCommand(Q.downloadID);
      }
      Q.downloadUserProgram = Ps;
      async function _s() {
        return oe.commands.executeCommand(Q.vexCommandHelpID);
      }
      Q.vexCommandHelp = _s;
      async function Ds() {
        return oe.commands.executeCommand(Q.vexCommandHelpShowAllID);
      }
      Q.vexCommandHelpShowAll = Ds;
    })((f = S.Command || (S.Command = {})));
    let k;
    ((K) => {
      (K.enableUserTerminalID = `${S.id}.General.EnableUserTerminal`),
        (K.buildTypeID = `${S.id}.Project.BuildType`),
        (K.runAfterDownload = `${S.id}.Project.RunAfterDownload`),
        (K.controllerChannel = `${S.id}.Controller.Channel`),
        (K.logEntriesID = `${S.id}.General.LogEntries`),
        (K.dfuAutoRecover = `${S.id}.System.DFU.AutoRecover`),
        (K.projectHomeID = `${S.id}.Project.Home`),
        (K.toolchainCPPPathID = `${S.id}.Cpp.Toolchain.Path`),
        (K.sdkCPPHomeID = `${S.id}.Cpp.Sdk.Home`),
        (K.sdkPythonHomeID = `${S.id}.Python.Sdk.Home`),
        (K.pylanceStubPathID = "python.analysis.stubPath"),
        (K.pylanceDiagnosticModePathID = "python.analysis.diagnosticMode"),
        (K.pylanceCheckingModeID = "python.analysis.typeCheckingMode"),
        (K.hostNameID = `${S.id}.WebsocketServer.HostAddress`),
        (K.portID = `${S.id}.WebsocketServer.Port`),
        (K.enableWebsocketServerID = `${S.id}.WebsocketServer.Enable`),
        (K.aiCameraHomeID = `${S.id}.AI.Camera.Image.Home`),
        (K.enableAI3dCameraUserTerminalID = `${S.id}.General.Enable3DCameraUserTerminal`);

      function po(ke) {
        let Te = [];
        return (
          ke.affectsConfiguration(K.enableUserTerminalID) &&
            Te.push(K.enableUserTerminalID),
          ke.affectsConfiguration(K.buildTypeID) && Te.push(K.buildTypeID),
          ke.affectsConfiguration(K.runAfterDownload) &&
            Te.push(K.runAfterDownload),
          ke.affectsConfiguration(K.controllerChannel) &&
            Te.push(K.controllerChannel),
          ke.affectsConfiguration(K.projectHomeID) && Te.push(K.projectHomeID),
          ke.affectsConfiguration(K.toolchainCPPPathID) &&
            Te.push(K.toolchainCPPPathID),
          ke.affectsConfiguration(K.sdkCPPHomeID) && Te.push(K.sdkCPPHomeID),
          ke.affectsConfiguration(K.sdkPythonHomeID) &&
            Te.push(K.sdkPythonHomeID),
          ke.affectsConfiguration(K.pylanceStubPathID) &&
            Te.push(K.pylanceStubPathID),
          ke.affectsConfiguration(K.pylanceDiagnosticModePathID) &&
            Te.push(K.pylanceDiagnosticModePathID),
          ke.affectsConfiguration(K.pylanceCheckingModeID) &&
            Te.push(K.pylanceCheckingModeID),
          ke.affectsConfiguration(K.hostNameID) && Te.push(K.hostNameID),
          ke.affectsConfiguration(K.portID) && Te.push(K.portID),
          ke.affectsConfiguration(K.enableWebsocketServerID) &&
            Te.push(K.enableWebsocketServerID),
          ke.affectsConfiguration(K.aiCameraHomeID) &&
            Te.push(K.aiCameraHomeID),
          ke.affectsConfiguration(K.enableAI3dCameraUserTerminalID) &&
            Te.push(K.enableAI3dCameraUserTerminalID),
          ke.affectsConfiguration(K.logEntriesID) && Te.push(K.logEntriesID),
          ke.affectsConfiguration(K.dfuAutoRecover) &&
            Te.push(K.dfuAutoRecover),
          Te
        );
      }
      K.getChangeSettingsList = po;
    })((k = S.Settings || (S.Settings = {})));
    let z;
    ((he) => {
      (he.getSDKVersionID = `${S.id}.sdk.version`),
        (he.downloadSDKID = `${S.id}.sdk.download`),
        (he.downloadToolchainID = `${S.id}.toolchain.download`),
        (he.getVexosVersionID = `${S.id}.vexos.version`),
        (he.downloadVexosID = `${S.id}.vexos.download`),
        (he.getVexosManifestID = `${S.id}.vexos.manifest`),
        (he.getVexaiVersionID = `${S.id}.vexai.version`),
        (he.downloadVexaiID = `${S.id}.vexai.download`),
        (he.verifyVexaiImageID = `${S.id}.vexai.verify`),
        (he.getVexaiImageManifestID = `${S.id}.vexai.manifest`),
        (he.getVexaiAppVersionID = `${S.id}.app.vexai.version`),
        (he.downloadAppVexaiID = `${S.id}.app.vexai.download`),
        (he.getVexaiAppListManifestID = `${S.id}.app.vexai.applist.manifest`),
        (he.getVexaiAppManifestID = `${S.id}.app.vexai.manifest`),
        (he.downloadVexaiAppID = `${S.id}.app.vexai.download`),
        (he.downloadDriverInstallerID = `${S.id}.driver-installer`);
      async function Uo(De, Le, Wt) {
        return (
          console.log("Send Command SDK Version", Wt),
          oe.commands.executeCommand(he.getSDKVersionID, De, Le, Wt)
        );
      }
      he.getSDKVersion = Uo;
      async function yo(De, Le, Wt, So) {
        return oe.commands.executeCommand(he.downloadSDKID, De, Le, Wt, So);
      }
      he.downloadSDK = yo;
      async function po(De) {
        return oe.commands.executeCommand(he.downloadToolchainID, De);
      }
      he.downloadToolchain = po;
      async function K(De, Le) {
        return oe.commands.executeCommand(he.getVexosVersionID, De, Le);
      }
      he.getVEXosVersions = K;
      async function ke(De, Le) {
        return oe.commands.executeCommand(he.downloadVexosID, De, Le);
      }
      he.downloadLatestVEXos = ke;
      async function Te(De) {
        return oe.commands.executeCommand(
          r.Extension.ResourceManager.downloadVexaiAppID,
          De
        );
      }
      he.downloadVEXaiApp = Te;
      async function Wo(De, Le) {
        return oe.commands.executeCommand(he.getVexosManifestID, De, Le);
      }
      he.getLatestVEXosManifest = Wo;
      async function Go(De) {
        return oe.commands.executeCommand(he.getVexaiAppListManifestID, De);
      }
      he.getVEXaiAppListVersions = Go;
      async function Jo(De, Le) {
        return oe.commands.executeCommand(he.getVexaiAppManifestID, De, Le);
      }
      he.getVEXaiAppVersions = Jo;
      async function qo(De, Le) {
        return oe.commands.executeCommand(he.downloadVexaiID, De, Le);
      }
      he.downloadLatestVEXaiImage = qo;
      async function Ko(De) {
        return oe.commands.executeCommand(he.getVexaiImageManifestID, De);
      }
      he.getLatestVEXaiManifest = Ko;
      async function Qo(De, Le) {
        return oe.commands.executeCommand(he.verifyVexaiImageID, De, Le);
      }
      he.verifyVEXaiImage = Qo;
      async function Yo(De, Le) {
        return oe.commands.executeCommand(he.downloadDriverInstallerID, De, Le);
      }
      he.downloadDriverInstaller = Yo;
    })((z = S.ResourceManager || (S.ResourceManager = {})));
    let Z;
    ((ue) => {
      (ue.v5BrainID = `vex-${"V5"}-${"Brain"}`),
        (ue.expBrainID = `vex-${"EXP"}-${"Brain"}`),
        (ue.iq2BrainID = `vex-${"IQ2"}-${"Brain"}`),
        (ue.v5ControllerID = `vex-${"V5"}-${"Controller"}`),
        (ue.expControllerID = `vex-${"EXP"}-${"Controller"}`),
        (ue.iq2ControllerID = `vex-${"IQ2"}-${"Controller"}`),
        (ue.fillerIcon = "question");

      function fe(le, de) {
        return le === "V5" && de === "Brain"
          ? ue.v5BrainID
          : le === "EXP" && de === "Brain"
          ? ue.expBrainID
          : le === "IQ2" && de === "Brain"
          ? ue.iq2BrainID
          : le === "V5" && de === "Controller"
          ? ue.v5ControllerID
          : le === "EXP" && de === "Controller"
          ? ue.expControllerID
          : le === "IQ2" && de === "Controller"
          ? ue.iq2ControllerID
          : ue.fillerIcon;
      }
      ue.getIconStr = fe;

      function me(le) {
        return `$(${le})`;
      }
      ue.wrapID = me;
    })((Z = S.Icons || (S.Icons = {})));
  })((s = r.Extension || (r.Extension = {})));
  let n;
  ((l) => {
    let c;
    ((b) => {
      function d() {
        let C = [],
          E = oe.extensions.getExtension(r.Extension.id).extensionUri,
          T = oe.Uri.joinPath(E, "resources", "extensions");
        return (
          ct.readdirSync(T.fsPath).forEach((f) => {
            let k = oe.Uri.joinPath(T, f),
              z = JSON.parse(
                new TextDecoder().decode(
                  ct.readFileSync(oe.Uri.joinPath(k, "package.json").fsPath)
                )
              ),
              Z = {
                id: `${z.publisher}.${z.name}`,
                extensionKind: oe.ExtensionKind.UI,
                isActive: !1,
                packageJSON: z,
                extensionUri: k,
                extensionPath: k.fsPath,
                exports: {},
                activate: async () => {},
              };
            C.push(Z);
          }),
          C
        );
      }
      b.all = d();

      function w(C) {
        let E = b.all.filter((T) => T.id === C);
        return E.length ? E[0] : void 0;
      }
      b.getExtension = w;
    })((c = l.Extensions || (l.Extensions = {})));
  })((n = r.Backup || (r.Backup = {})));
  let a;
  ((O) => {
    function c(f) {
      try {
        JSON.parse(f);
      } catch {
        return !1;
      }
      return !0;
    }
    O.isJsonString = c;

    function l() {
      return new Date().toLocaleString();
    }
    O.getDateString = l;
    async function d(f) {
      return () => f;
    }
    O.toPromise = d;

    function m() {
      let f = new TextDecoder(),
        k;
      return (
        at.type() === "Windows_NT"
          ? (k = f.decode(new Uint8Array([13, 10]).buffer))
          : at.type() === "Darwin"
          ? (k = f.decode(new Uint8Array([13]).buffer))
          : (k = f.decode(new Uint8Array([13]).buffer)),
        k
      );
    }
    O.getEndline = m;
    async function w(f) {
      return f < 0 && (f = 0), new Promise((k) => setTimeout(k, f));
    }
    O.asyncSleep = w;
    async function b(f, k) {
      if (!ct.existsSync(f.fsPath))
        throw new Error(`Unzip Fail: File does not exist @ ${f.fsPath}`);
      let z = k ? k.fsPath : ko.dirname(f.fsPath);
      console.log(`File Uri Basename: ${ko.dirname(f.fsPath)}`),
        console.log(`PathToUnzip: ${ko.dirname(z)}`);
      let Z = !1,
        S = !1;
      for (
        ct
          .createReadStream(`${f.fsPath}`)
          .pipe(
            js.Extract({
              path: `${z}`,
            })
          )
          .on("close", () => {
            console.log("Unzipper Close"), (Z = !0);
          })
          .on("error", () => {
            throw (
              ((Z = !0),
              (S = !0),
              console.log(new Error("Unzipper Close")),
              new Error("Unzip Fail: Read Stream Error"))
            );
          });
        !Z || S;

      )
        await new Promise((V) => setTimeout(V, 500));
      return S;
    }
    O.unzipFile = b;
    async function C(f, k, z) {
      let Z = z?.updateTimeMs ? z?.updateTimeMs : 1;
      if (!ct.existsSync(f.fsPath))
        return {
          checksum: "",
          errorCode: -1,
        };
      let S = ct.statSync(f.fsPath);
      if (!S.isFile())
        return {
          checksum: "",
          errorCode: -2,
        };
      var W = ct.createReadStream(f.fsPath, {
        highWaterMark: 1024 * 1024,
      });
      let V = Rs.createHash("md5", {
        highWaterMark: 1024 * 1024,
      });
      for (W.pipe(V); !W.destroyed; ) {
        let X = W.bytesRead / S.size;
        z?.cb(X), await r.Utils.asyncSleep(Z);
      }
      return (
        z?.cb(1),
        {
          checksum: V.digest(k),
          errorCode: 0,
        }
      );
    }
    O.getMd5FromFile = C;

    function E(f, k) {
      let z = {
        command: "unknown",
        details: "",
        json: "",
        statusCode: 0,
      };
      if ("vexaicommsI" in f) {
        let Z = k || new TextDecoder().decode(f.data),
          S = JSON.parse(Z),
          W = "";
        if (f?.cmdID === F.Commands.run) {
          let V = Buffer.from(S.error, "base64").toString("utf-8"),
            X = Buffer.from(S.stderr, "base64").toString("utf-8"),
            ye = Buffer.from(S.stdout, "base64").toString("utf-8"),
            se = S.exitcode;
          W = `${F.getErrorCodeDetails(f.exitCode)} ${f.details} | CMD: ${
            f.cmdStr
          }
RESP:
stdout:${ye}
stderr:${X}
error:${V}
exitcode:${se}
`;
        } else
          f?.cmdID === F.Commands.deviceInfo
            ? (W = `${F.getErrorCodeDetails(f.exitCode)} ${f.details} | CMD: ${
                f.cmdStr
              }`)
            : (W = `${F.getErrorCodeDetails(f.exitCode)} ${f.details} | CMD: ${
                f.cmdStr
              } 
RESP: ${Z}`);
        z = {
          command: f?.cmdID ? f.cmdID : F.Commands.unknown,
          details: W,
          statusCode: f.exitCode,
          json: Z || "{}",
        };
      } else
        "uuuI" in f
          ? (z = {
              command: f?.cmdID ? f.cmdID : Pe.CommandID.unknown,
              details: `${Pe.getErrorCodeDetails(f.exitCode)} ${f.stderr} | ${
                f.cmdStr
              }`,
              statusCode: f.exitCode,
              json: k || "{}",
            })
          : "vexcomI" in f
          ? f.exitCode === x.ExitCode.vexSucess
            ? (z = {
                command: f?.cmdID ? f.cmdID : x.CommandID.unknown,
                details: `${x.getErrorCodeDetails(f.exitCode)} ${f.stderr} | ${
                  f.cmdStr
                } `,
                statusCode: f.exitCode,
                json: k || "{}",
              })
            : (z = {
                command: f?.cmdID ? f.cmdID : x.CommandID.unknown,
                details: `${x.getErrorCodeDetails(f.exitCode)} | ${f.cmdStr} 
${f.stdout}
${f.stderr}
 `,
                statusCode: f.exitCode,
                json: k || "{}",
              })
          : (z = {
              command: f?.cmdID ? f.cmdID : x.CommandID.unknown,
              details: `${x.getErrorCodeDetails(f.exitCode)} ${f.stderr} | ${
                f.cmdStr
              }`,
              statusCode: f.exitCode,
              json: k || "{}",
            });
      return z;
    }
    O._toCommandResponse = E;
    let T;
    ((ye) => {
      function f(se) {
        let G = parseInt(se),
          re = (G >>> 24) & 255,
          fe = (G >>> 16) & 255,
          me = (G >>> 8) & 255,
          ue = G & 255;
        return `${re}.${fe}.${me}.${ue}`;
      }
      ye.toVersion = f;

      function k(se) {
        let G = [],
          re = RegExp(/VEXOS_(V5|EXP|IQ2)_\d_\d_\d_\d/);
        return (
          se.forEach((fe) => {
            re.test(fe)
              ? G.push(fe)
              : console.error(`Version Not Compadable: ${fe}`);
          }),
          G.sort(z),
          G[0] ? G[0] : []
        );
      }
      ye.getLatestVEXosVersion = k;

      function z(se, G) {
        var re = se.toUpperCase(),
          fe = G.toUpperCase();
        let me = re.split("_"),
          ue = fe.split("_"),
          le = {
            major: Number(me[2]),
            minor: Number(me[3]),
            build: Number(me[4]),
            beta: Number(me[5]),
          },
          de = {
            major: Number(ue[2]),
            minor: Number(ue[3]),
            build: Number(ue[4]),
            beta: Number(ue[5]),
          };
        return le.major > de.major
          ? -1
          : le.major < de.major
          ? 1
          : le.minor > de.minor
          ? -1
          : le.minor < de.minor
          ? 1
          : le.build > de.build
          ? -1
          : le.build < de.build
          ? 1
          : le.beta > de.beta
          ? de.beta === 0
            ? 1
            : -1
          : le.beta < de.beta
          ? le.beta === 0
            ? -1
            : 1
          : 0;
      }

      function Z(se) {
        let G = [],
          re = RegExp(/\d\.\d\.\d\.\d/);
        return (
          se.forEach((fe) => {
            re.test(fe)
              ? G.push(fe)
              : console.error(`Version Not Compadable: ${fe}`);
          }),
          G.sort(S),
          G[0] ? G[0] : []
        );
      }
      ye.getLatestControllerVersion = Z;

      function S(se, G) {
        var re = se.toUpperCase(),
          fe = G.toUpperCase();
        let me = re.split("."),
          ue = fe.split("."),
          le = {
            major: Number(me[0]),
            minor: Number(me[1]),
            build: Number(me[2]),
            beta: Number(me[3]),
          },
          de = {
            major: Number(ue[0]),
            minor: Number(ue[1]),
            build: Number(ue[2]),
            beta: Number(ue[3]),
          };
        return le.major > de.major
          ? -1
          : le.major < de.major
          ? 1
          : le.minor > de.minor
          ? -1
          : le.minor < de.minor
          ? 1
          : le.build > de.build
          ? -1
          : le.build < de.build
          ? 1
          : le.beta > de.beta
          ? de.beta === 0
            ? 1
            : -1
          : le.beta < de.beta
          ? le.beta === 0
            ? -1
            : 1
          : 0;
      }

      function W(se) {
        let G = 0,
          re = 0,
          fe = 0,
          me = 0,
          ue = "";
        return (
          se.forEach(function (le) {
            let de = 0,
              _t = 0,
              Dt = 0,
              it = -1,
              Ut = le.split(".");
            if (
              ((de = parseInt(Ut[0])),
              (_t = parseInt(Ut[1])),
              (Dt = parseInt(Ut[2])),
              (it = parseInt(Ut[3])),
              !(de < G) &&
                (de > G && ((re = 0), (fe = 0), (me = -1)),
                !(_t < re) &&
                  (_t > re && ((fe = 0), (me = -1)),
                  !(Dt < fe) && (Dt > fe && (me = -1), !(it < me)))))
            ) {
              if (me > it)
                if (it === 0) me = it;
                else return;
              else if (me < it) {
                if (me === 0) return;
                me = it;
              }
              (G = de), (re = _t), (fe = Dt), (me = it), (ue = le);
            }
          }),
          ue
        );
      }
      ye.getLatestFileVersion = W;

      function V(se) {
        let G = se.split("_");
        return G.shift(), G.shift(), G.join(".");
      }
      ye.fileNameToVersion = V;

      function X(se, G) {
        let re = se.split(".");
        return re.unshift(G), re.unshift("VEXOS"), re.join("_");
      }
      ye.versionToFileName = X;
    })((T = O.vexos || (O.vexos = {})));
  })((a = r.Utils || (r.Utils = {})));
})(i || (i = {}));
var I = class {
  static _toCommandResponse(t, e) {
    return {
      command: t?.cmdID ? t.cmdID : x.CommandID.unknown,
      details: `${x.getErrorCodeDetails(t.exitCode)} ${t.stderr} | ${t.cmdStr}`,
      statusCode: t.exitCode,
      json: e || "{}",
    };
  }
  isTypeOf(t) {
    let e = I;
    return t instanceof I;
  }
  get platform() {
    return this._platform;
  }
  get device() {
    return this._device;
  }
  get bootMode() {
    return this._bootMode;
  }
  static async listDevices(t, e = void 0) {
    let o = i.Extension.getVexcomUri(i.Extension.context),
      s = new x(o.fsPath, t, {
        active: !1,
        maxCmds: 0,
      }),
      n = "";
    s.on("Data", (r, c) => {
      n += c;
    });
    let a = await s.listUSB(e);
    return I._toCommandResponse(a, n);
  }
};
((t) => {
  let _;
  ((r) => (
    (r.unknown = "unknown"),
    (r.dfu = "dfu"),
    (r.ram = "ram"),
    (r.rom = "rom"),
    (r.app = "app")
  ))((_ = t.BootMode || (t.BootMode = {})));
})(I || (I = {}));
var oo = class {
  constructor(t) {
    this._devicePath = t;
  }
};
var ks = require("serialport"),
  At = class extends oo {
    constructor(e, o = 115200) {
      super(e);
      e &&
        (this._serialPort = new ks.SerialPort({
          path: e,
          baudRate: o,
          parity: "none",
          stopBits: 1,
          xoff: !0,
          xon: !0,
          autoOpen: !1,
        }));
    }
    get serialPort() {
      return this?._serialPort;
    }
    get isOpen() {
      return this?._serialPort?.isOpen;
    }
    write(e) {
      this?._serialPort?.write(e, "utf8");
    }
    read(e) {
      this?._serialPort.read(e);
    }
    close(e) {
      e ? this?._serialPort.close((o) => e(o)) : this?._serialPort.close();
    }
    open(e) {
      e ? this?._serialPort.open((o) => e(o)) : this?._serialPort.open();
    }
    registerCallback(e, o) {
      switch (e) {
        case "OnRecieveData":
          this?._serialPort?.removeAllListeners("data"),
            this?._serialPort?.on("data", o),
            console.log(this?._serialPort.listeners("data"));
        case "OnOpen":
          this?._serialPort?.on("open", o);
      }
    }
  };
var $o = class extends oo {
  constructor(e, o) {
    super(e);
    let s = i.Extension.getVexcomUri(i.Extension.context);
    this._vexcom = new x(s.fsPath, this._devicePath, {
      active: !0,
      maxCmds: 0,
    });
  }
  get childProcess() {
    return this?._vexcomCP;
  }
  get isOpen() {
    return this._vexcomCP ? !this._vexcomCP?.exitCode : !1;
  }
  async open(e) {
    if (this.isOpen) return;
    let o = this._vexcom.openUserPort(this._devicePath);
    return (
      (this._vexcomCP = await o[0]),
      console.log(JSON.stringify(o[0])),
      e && e(void 0),
      i.Utils._toCommandResponse(await o[1])
    );
  }
  write(e) {
    this?._vexcomCP?.stdin?.write(e, "utf8");
  }
  read(e) {}
  close(e) {
    this._vexcomCP &&
      (this?._vexcomCP.stdin.write(new Uint8Array([3])), e && e(void 0)),
      (this._vexcomCP = void 0);
  }
  registerCallback(e, o) {
    switch (e) {
      case "OnRecieveData":
        this?._vexcom?.on("UserRX", (s, n) => o(n));
      case "OnOpen":
    }
  }
};
var No = L(require("os")),
  J = class extends I {
    constructor(e, o = !1, s) {
      super();
      this._vexcomDataHolder = "";
      this._dataResultArr = [];
      this._needsVexosUpdate = !1;
      (this._vexcomDataHolder = ""),
        (this._dataResultArr = []),
        (this._platform = e.platform),
        (this._device = e.device),
        (this._robotName = e.robotName),
        (this._communicationPath = e.communication),
        (this._userPath = e.user),
        (this._id = e.id),
        (this._teamNumber = e.teamNumber),
        (this._systemInfoJSON = e.json),
        this.parseSystemInfoJSON(this._systemInfoJSON),
        !this._userPath &&
        this._platform === i.Platform.V5 &&
        this._device === i.Device.Controller
          ? (this._userPort = new $o(this._communicationPath))
          : (this._userPort = new At(this._userPath));
      let n = i.Extension.getVexcomUri(i.Extension.context);
      (this._vexcom = new x(n.fsPath, this._communicationPath, {
        active: !0,
        maxCmds: 0,
      })),
        this._vexcom.on("Data", (a, r) => {
          this._onVexcomDataRecieved(this, a, r);
        }),
        this._vexcom.on("Error", (a, r) => {
          this._onVexcomErrorRecieved(this, a, r);
        }),
        this._vexcom.on("Exit", (a, r) => {
          this._onVexcomExitRecieved(this, a, r);
        });
    }
    async play(e) {
      let o = await this._vexcom.play(e);
      return I._toCommandResponse(o);
    }
    async stop() {
      let e = await this._vexcom.stop();
      return I._toCommandResponse(e);
    }
    async erase(e) {
      let o = await this._vexcom.eraseUserProgram(e);
      return I._toCommandResponse(o);
    }
    async downloadPythonVM(e) {
      let o = {
          location: Jt.ProgressLocation.Notification,
          title: "Python VM Update: ",
          cancellable: !1,
        },
        s = await this._handleProgress(
          () => this._vexcom.downloadPythonVM(e?.fsPath),
          o
        );
      return I._toCommandResponse(s);
    }
    async systemInfo() {
      let e = await this._vexcom.systemInfo(),
        o = I._toCommandResponse(e, this._dataResultArr.shift());
      return (
        o.statusCode !== x.ExitCode.vexCMDQueueDownloadActive &&
          ((this._systemInfoJSON = o.json),
          this.parseSystemInfoJSON(this._systemInfoJSON)),
        o
      );
    }
    static async systemInfo(e) {
      let o = i.Extension.getVexcomUri(i.Extension.context),
        n = await new x(o.fsPath, e, {
          active: !1,
          maxCmds: 0,
        }).systemInfo();
      return I._toCommandResponse(n, n.stdout);
    }
    static async listDevices(e) {
      let o = i.Extension.getVexcomUri(i.Extension.context),
        s = new x(o.fsPath, e, {
          active: !1,
          maxCmds: 0,
        }),
        n = "";
      s.on("Data", (r, c) => {
        n += c;
      });
      let a = await s.listUSB();
      return I._toCommandResponse(a, n);
    }
    async systemStatus() {
      let e = await this._vexcom.systemStatus(),
        o = I._toCommandResponse(e, this._dataResultArr.shift());
      return (
        (this._systemInfoJSON = o.json),
        this.parseSystemInfoJSON(this._systemInfoJSON),
        o
      );
    }
    static async getVexcomVersion(e) {
      let o = i.Extension.getVexcomUri(i.Extension.context),
        s = new x(o.fsPath, "", {
          active: !0,
          maxCmds: 0,
        }),
        n = "";
      s.on("Data", (r, c) => {
        n += c;
      });
      let a = await s.getVersion();
      return I._toCommandResponse(a, n);
    }
    static async systemDFU(e, o) {
      let s = i.Extension.getVexcomUri(i.Extension.context),
        n = new x(s.fsPath, "", {
          active: !1,
          maxCmds: 0,
        }),
        a = {
          location: Jt.ProgressLocation.Notification,
          title: "Controller Usb Update: ",
          cancellable: !1,
        },
        r = await n.recoverFromDFU(o.toString().toLowerCase());
      return I._toCommandResponse(r);
    }
    async setTeamName(e) {
      let o = await this._vexcom.setTeamNumber(e);
      return (
        o.exitCode === x.ExitCode.vexSucess && (this._teamNumber = e),
        I._toCommandResponse(o)
      );
    }
    async setRobotName(e) {
      let o = await this._vexcom.setRobotName(e);
      return (
        o.exitCode === x.ExitCode.vexSucess && (this._robotName = e),
        I._toCommandResponse(o)
      );
    }
    async screenGrab(e) {
      let o = await this._vexcom.screenGrab(e.fsPath);
      return I._toCommandResponse(o);
    }
    async uploadEventLog(e = 1e3) {
      let o = {
          location: Jt.ProgressLocation.Notification,
          title: "Upload Event Log: ",
          cancellable: !1,
        },
        s = await this._handleProgress(async () => {
          let n = this._vexcom.uploadEventLog(e);
          return await i.Utils.asyncSleep(1e3), n;
        }, o);
      return I._toCommandResponse(s, this._dataResultArr.shift());
    }
    async batteryMedic() {
      let e = await this._vexcom.batteryMedic();
      return I._toCommandResponse(e);
    }
    async systemUpdate(e, o = !1) {
      let s = {
          location: Jt.ProgressLocation.Notification,
          title: "Vexos Update: ",
          cancellable: !1,
        },
        n = await this._handleProgress(
          () => this._vexcom.sytemUpdate(e.fsPath, o),
          s
        );
      return I._toCommandResponse(n);
    }
    parseSystemInfoJSON(e) {
      let o = JSON.parse(e),
        s;
      if (o.v5) s = o.v5;
      else if (o.iq2) s = o.iq2;
      else if (o.exp) s = o.exp;
      else if (o?.unknown?.controller_boot) s = o.unknown;
      else {
        this._systemInfoJSON = "{}";
        return;
      }
      (this._filesInfo = o.files),
        (this._systemInfo = s),
        s?.brain?.bootloader
          ? (s?.brain?.bootloader === I.BootMode.ram ||
            s?.brain?.bootloader === I.BootMode.rom
              ? (this._bootMode = s?.brain?.bootloader)
              : (this._bootMode = I.BootMode.unknown),
            (this._robotName = ""),
            (this._id = ""),
            (this._teamNumber = ""))
          : s?.brain
          ? ((this._bootMode = I.BootMode.app),
            (this._robotName = s.brain.name),
            (this._id = s.brain.ssn),
            (this._teamNumber = s.brain.team))
          : s?.controller
          ? ((this._bootMode = I.BootMode.app),
            (this._robotName = ""),
            (this._id = ""),
            (this._teamNumber = ""))
          : s?.controller_boot &&
            ((this._bootMode = I.BootMode.rom),
            (this._robotName = ""),
            (this._id = ""),
            (this._teamNumber = ""));
    }
    parseSystemStatusJSON(e) {
      let o = JSON.parse(e),
        s;
      if (o.v5) s = o.v5;
      else if (o.iq2) s = o.iq2;
      else if (o.exp) s = o.exp;
      else {
        this._systemInfoJSON = "{}";
        return;
      }
      (this._filesInfo = o.files),
        (this._systemInfo = s),
        s?.system?.bootloader
          ? (s?.brain?.bootloader === I.BootMode.ram ||
            s?.brain?.bootloader === I.BootMode.rom
              ? (this._bootMode = s?.brain?.bootloader)
              : (this._bootMode = I.BootMode.unknown),
            (this._robotName = `${this._bootMode}`),
            (this._id = ""),
            (this._teamNumber = ""))
          : s?.brain
          ? ((this._bootMode = I.BootMode.app),
            (this._robotName = s.brain.name),
            (this._id = s.brain.ssn),
            (this._teamNumber = s.brain.team))
          : s?.controller;
    }
    async _isControllerRadioLinked(e = x.CommandID.unknown) {
      if (
        (await this.systemInfo(),
        (Number(this._systemInfo?.controller?.flags) & J.RADIO_LINK) !==
          J.RADIO_LINK)
      ) {
        let o = {
          command: e,
          details: `${this._platform}
 ${this._device} not linked to brain`,
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
        return await this.systemInfo(), o;
      }
      return null;
    }
    async _isControllerTethered(e = x.CommandID.unknown) {
      if (
        (await this.systemInfo(),
        (Number(this._systemInfo?.controller?.flags) & J.TETHER_LINK) !==
          J.TETHER_LINK)
      ) {
        let o = {
          command: e,
          details: `${this._platform} ${this._device} not tethered to brain`,
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
        return await this.systemInfo(), o;
      }
      return null;
    }
    get robotName() {
      return this._robotName;
    }
    get id() {
      return this._id;
    }
    get teamNumber() {
      return this._teamNumber;
    }
    get bootMode() {
      return this._bootMode;
    }
    get platform() {
      return this._platform;
    }
    get device() {
      return this._device;
    }
    get json() {
      return this._systemInfoJSON;
    }
    get vexComSystemInfo() {
      return this._systemInfo;
    }
    get vexcomFilesInfo() {
      return this._filesInfo;
    }
    get activeCommand() {
      return this._vexcom.activeCommand.cmdID;
    }
    get communication() {
      return this._communicationPath;
    }
    get user() {
      return this._userPath;
    }
    get userPort() {
      return this?._userPort;
    }
    async _handleProgress(e, o) {
      let s,
        n = async (a, r) => (
          a?.report({
            increment: 0,
            message: "preparing . . . ",
          }),
          await e()
        );
      {
        let a = Jt.window.withProgress(o, async (r, c) => {
          this._progress
            ? ((s = n(r, c)), await s)
            : ((this._lastProgress = 0),
              (this._progress = r),
              (s = n(r, c)),
              await s,
              (this._progress = void 0));
        });
        for (; !s; ) await i.Utils.asyncSleep(100);
      }
      return s;
    }
    _onVexcomDataRecieved(e, o, s) {
      switch (o) {
        case x.CommandID.systemStatus:
        case x.CommandID.systemInfo:
          e._vexcomDataHolder += s;
          break;
        case x.CommandID.controllerRadioUpdate:
        case x.CommandID.controllerUsbUpdate:
        case x.CommandID.downloadUserProgram:
        case x.CommandID.downloadPythonVM:
        case x.CommandID.systemUpdate:
          let n;
          try {
            n = JSON.parse(s) ? JSON.parse(s) : "";
          } catch {
            return;
          }
          let a = n.percent - this._lastProgress;
          (this._lastProgress = n.percent),
            this._progress?.report({
              increment: a,
              message: `${n.action.toUpperCase()}:${n.phase.toUpperCase()} ${
                n.percent
              }%`,
            });
          break;
        case x.CommandID.uploadEventLog:
          console.log(s);
          let r = [];
          s = e._vexcomDataHolder + s;
          let c = 0;
          if ((No.EOL, No.type() === "Windows_NT")) {
            for (let l = 0; l < s.length - 2; l++)
              if (
                s[l] === "}" &&
                s[l + 1] === "\r" &&
                s[l + 2] ===
                  `
`
              ) {
                let d = s.substring(c, l + 3);
                i.Utils.isJsonString(d) && (r.push(JSON.parse(d)), (c = l + 3));
              }
          } else
            for (let l = 0; l < s.length - 1; l++)
              if (
                s[l] === "}" &&
                s[l + 1] ===
                  `
`
              ) {
                let d = s.substring(c, l + 2);
                i.Utils.isJsonString(d) && (r.push(JSON.parse(d)), (c = l + 2));
              }
          c !== s.length
            ? (e._vexcomDataHolder = s.substring(c, s.length))
            : (e._vexcomDataHolder = ""),
            r.forEach((l) => {
              if (l?.percent) {
                let d = l.percent - this._lastProgress;
                (this._lastProgress = l.percent),
                  this._progress?.report({
                    increment: d,
                    message: `${l.action.toUpperCase()}:${l.phase.toUpperCase()} ${
                      l.percent
                    }%`,
                  });
              }
              l?.log && (e._vexcomDataHolder = JSON.stringify(l));
            });
          break;
      }
    }
    _onVexcomErrorRecieved(e, o, s) {}
    _onVexcomExitRecieved(e, o, s) {
      switch (o) {
        case x.CommandID.systemStatus:
        case x.CommandID.systemInfo:
          e._dataResultArr.push(e._vexcomDataHolder),
            (e._vexcomDataHolder = "");
          break;
        case x.CommandID.uploadEventLog:
          e._dataResultArr.push(e._vexcomDataHolder),
            (e._vexcomDataHolder = "");
          break;
      }
    }
    static isTypeOf(e) {
      return e instanceof J;
    }
    static toCommandResponse(e, o) {
      return {
        command: e?.cmdID ? e.cmdID : x.CommandID.unknown,
        details: `${x.getErrorCodeDetails(e.exitCode)} ${e.stderr} | ${
          e.cmdStr
        }`,
        statusCode: e.exitCode,
        json: o || "{}",
      };
    }
  };
((s) => {
  (s.NO_CONNECT = 0), (s.TETHER_LINK = 1), (s.RADIO_LINK = 2);
  let o;
  ((r) => (
    (r[(r.V5ControllerNotSupported = -1)] = "V5ControllerNotSupported"),
    (r[(r.SerialPortIOError = -2)] = "SerialPortIOError")
  ))((o = s.Error || (s.Error = {})));
})(J || (J = {}));
var $s = L(require("vscode"));
var Ct = class extends J {
  constructor(t, e = !1, o) {
    super(t, e, o);
  }
  async downloadUserProgram(t, e, o, s, n = !1) {
    switch (this._device) {
      case i.Device.Brain:
        if (this._bootMode !== I.BootMode.app)
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} running ${this._bootMode} bootloader`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        let a = await this._vexcom.downloadUserProgram(
          t,
          e,
          s.fsPath,
          o,
          n,
          !1
        );
        return I._toCommandResponse(a);
      case i.Device.Unknown:
      default:
        return {
          command: x.CommandID.downloadUserProgram,
          details: "Unknown Device Connected",
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
    }
  }
  async systemUpdate(t, e = !1) {
    let o = {
        location: $s.ProgressLocation.Notification,
        title: "Vexos Update: ",
        cancellable: !1,
      },
      s = await this._handleProgress(
        () => this._vexcom.sytemUpdate(t.fsPath, e),
        o
      );
    return I._toCommandResponse(s);
  }
  get needsVexosUpdate() {
    return this._needsVexosUpdate;
  }
  set needsVexosUpdate(t) {
    this._needsVexosUpdate = t;
  }
};
var Ns = L(require("vscode"));
var Je = class extends J {
  constructor(e, o = !1, s) {
    super(e, o, s);
    this._needsRadioUpdate = !1;
    this._needsUsbUpDate = !1;
  }
  async downloadUserProgram(
    e,
    o,
    s,
    n,
    a = !1,
    r = x.DownloadChannel.vexNoChannel
  ) {
    this._userPort.close();
    let c = await super._isControllerRadioLinked(),
      l = await super._isControllerTethered();
    if (c && l) return (c.command = x.CommandID.downloadUserProgram), c;
    let d = {
        location: Ns.ProgressLocation.Notification,
        title: "Program Download: ",
        cancellable: !1,
      },
      m = await this._handleProgress(
        () => this._vexcom.downloadUserProgram(e, o, n.fsPath, s, a, !0, r),
        d
      );
    return console.log(m), this._userPort.open(), I._toCommandResponse(m);
  }
  async play(e) {
    this._userPort.close();
    let o = await super.systemInfo();
    if (o.statusCode !== x.ExitCode.vexSucess) return o;
    let s = await super.play(e);
    return this._userPort.open(), s;
  }
  async stop() {
    this._userPort.close();
    let e = await super.systemInfo();
    return e.statusCode !== x.ExitCode.vexSucess ? e : await super.stop();
  }
  async erase(e) {
    this._userPort.close();
    let o = await super.erase(e),
      s = await super.systemInfo();
    return s.statusCode !== x.ExitCode.vexSucess
      ? s
      : (this._userPort.open(), o);
  }
  async setRobotName(e) {
    this._userPort.close();
    let o = await super.setRobotName(e),
      s = await super.systemInfo();
    return s.statusCode !== x.ExitCode.vexSucess
      ? s
      : (this._userPort.open(), o);
  }
  async setTeamName(e) {
    this._userPort.close();
    let o = await super.setTeamName(e),
      s = await super.systemInfo();
    return s.statusCode !== x.ExitCode.vexSucess
      ? s
      : (this._userPort.open(), o);
  }
  async screenGrab(e) {
    this._userPort.close();
    let o = await super.screenGrab(e);
    return this._userPort.open(), o;
  }
  async uploadEventLog() {
    this._userPort.close();
    let e = await super._isControllerRadioLinked(),
      o = await super._isControllerTethered();
    if (e && o) return (e.command = x.CommandID.uploadEventLog), e;
    let s = await super.uploadEventLog();
    return this._userPort.open(), s;
  }
  async batteryMedic() {
    this._userPort.close();
    let e = await super.batteryMedic();
    return this._userPort.open(), e;
  }
  async downloadPythonVM() {
    this._userPort.close();
    let e = await super.downloadPythonVM();
    return this._userPort.open(), e;
  }
  async systemInfo() {
    let e = this._userPort.isOpen;
    e && this._userPort.close();
    let o = await super.systemInfo();
    return e && this._userPort.open(), o;
  }
  async systemUpdate(e, o = !1) {
    let s = this._userPort.isOpen;
    s && this._userPort.close();
    let n = await super._isControllerTethered(x.CommandID.systemUpdate);
    if (n) return n;
    let a = await this._isBrainBatteryLow(x.CommandID.systemUpdate);
    if (a) return a;
    let r = await super.systemUpdate(e, o);
    return s && this._userPort.open(), r;
  }
  async _isBrainBatteryLow(e = x.CommandID.unknown) {
    if ((await super.systemInfo(), this._systemInfo?.system?.low_battery)) {
      let o = {
        command: e,
        details: `${this._platform} ${this._device},  ${this._platform} ${i.Device.Brain} battery (${this._systemInfo?.system?.battery}%) low. VEXos update not allowed`,
        json: "{}",
        statusCode: x.ExitCode.vexError,
      };
      return await super.systemInfo(), o;
    }
    return null;
  }
  get needsRadioUpdate() {
    return this._needsRadioUpdate;
  }
  set needsRadioUpdate(e) {
    this._needsRadioUpdate = e;
  }
  get needsUsbUpdate() {
    return this._needsUsbUpDate;
  }
  set needsUsbUpdate(e) {
    this._needsUsbUpDate = e;
  }
  get needsVexosUpdate() {
    return (
      (this._needsVexosUpdate = this._needsUsbUpDate && this._needsRadioUpdate),
      this._needsUsbUpDate && this._needsRadioUpdate
    );
  }
  set needsVexosUpdate(e) {
    this._needsVexosUpdate = e;
  }
};
var Ms = L(require("vscode"));
var vt = class extends J {
  constructor(t, e = !1, o) {
    super(t, e, o);
  }
  async downloadUserProgram(t, e, o, s, n = !1) {
    switch (this._device) {
      case i.Device.Brain:
        if (this._bootMode !== I.BootMode.app)
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} running ${this._bootMode} bootloader`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        let a = await this._vexcom.downloadUserProgram(
          t,
          e,
          s.fsPath,
          o,
          n,
          !1
        );
        return I._toCommandResponse(a);
      case i.Device.Unknown:
      default:
        return {
          command: x.CommandID.downloadUserProgram,
          details: "Unknown Device Connected",
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
    }
  }
  async systemUpdate(t, e = !1) {
    let o = {
        location: Ms.ProgressLocation.Notification,
        title: "Vexos Update: ",
        cancellable: !1,
      },
      s = await this._handleProgress(
        () => this._vexcom.sytemUpdate(t.fsPath, e),
        o
      );
    return I._toCommandResponse(s);
  }
  get needsVexosUpdate() {
    return this._needsVexosUpdate;
  }
  set needsVexosUpdate(t) {
    this._needsVexosUpdate = t;
  }
};
var so = L(require("vscode"));
var et = class extends J {
  constructor(e, o = !1, s) {
    super(e, o, s);
    this._needsRadioUpdate = !1;
    this._needsUsbUpDate = !1;
  }
  async downloadUserProgram(e, o, s, n, a = !1) {
    switch (this._device) {
      case i.Device.Controller:
        if (!this._systemInfo?.controller?.flags)
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} No Radio Status`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        if (
          (Number(this._systemInfo?.controller?.flags) & 2) !== 2 &&
          this._systemInfo?.brain === void 0
        )
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} Not Linked to brain`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        let r = {
          location: so.ProgressLocation.Notification,
          title: "Program Download: ",
          cancellable: !1,
        };
        if (
          this._platform === i.Platform.EXP ||
          this._platform === i.Platform.IQ2
        ) {
          let l = await this._handleProgress(
            () => this._vexcom.downloadUserProgram(e, o, n.fsPath, s, a, !0),
            r
          );
          return I._toCommandResponse(l);
        } else
          return {
            command: x.CommandID.downloadUserProgram,
            details: "Unknown Device Connected",
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
      case i.Device.Unknown:
      default:
        return {
          command: x.CommandID.downloadUserProgram,
          details: "Unknown Device Connected",
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
    }
  }
  async controllerUsbUpdate(e) {
    let o = {
        location: so.ProgressLocation.Notification,
        title: `${this.platform} ${this.device} Usb Update: `,
        cancellable: !1,
      },
      s = await this._handleProgress(async () => {
        this._progress?.report({
          increment: 50,
          message: "50%",
        });
        let n = await this._vexcom.controllerAtmelFirmwareUpdate(e.fsPath);
        return (
          n.exitCode === x.ExitCode.vexSucess &&
            ((this._needsUsbUpDate = !1),
            this._progress?.report({
              increment: 50,
              message: "100%",
            }),
            await i.Utils.asyncSleep(100)),
          n
        );
      }, o);
    return I._toCommandResponse(s);
  }
  async controllerRadioUpdate(e) {
    let o = {
        location: so.ProgressLocation.Notification,
        title: `${this.platform} ${this.device} Radio Update: `,
        cancellable: !1,
      },
      s = await this._handleProgress(
        () => this._vexcom.controllerRadioFirmwareUpdate(e.fsPath),
        o
      );
    return (
      s.exitCode === x.ExitCode.vexSucess && (this._needsRadioUpdate = !1),
      I._toCommandResponse(s)
    );
  }
  async controllerUpdate(e) {
    let o = {
      location: so.ProgressLocation.Notification,
      title: `${this.platform} ${this.device} Update: `,
      cancellable: !1,
    };
    return (
      await this.controllerRadioUpdate(e), await this.controllerUsbUpdate(e)
    );
  }
  static async controllerUsbUpdate(e) {
    let o = i.Extension.getVexcomUri(i.Extension.context),
      s = new x(o.fsPath, "", {
        active: !1,
        maxCmds: 0,
      }),
      n = {
        location: so.ProgressLocation.Notification,
        title: "Controller Usb Update: ",
        cancellable: !1,
      },
      a = await s.controllerAtmelFirmwareUpdate(e.fsPath);
    return I._toCommandResponse(a);
  }
  async uploadEventLog() {
    let e = await super._isControllerRadioLinked();
    return e
      ? ((e.command = x.CommandID.uploadEventLog), e)
      : await super.uploadEventLog();
  }
  get needsRadioUpdate() {
    return this._needsRadioUpdate;
  }
  set needsRadioUpdate(e) {
    this._needsRadioUpdate = e;
  }
  get needsUsbUpdate() {
    return this._needsUsbUpDate;
  }
  set needsUsbUpdate(e) {
    this._needsUsbUpDate = e;
  }
  get needsVexosUpdate() {
    return (
      (this._needsVexosUpdate = this._needsUsbUpDate && this._needsRadioUpdate),
      this._needsUsbUpDate && this._needsRadioUpdate
    );
  }
  set needsVexosUpdate(e) {
    this._needsVexosUpdate = e;
  }
};
var As = L(require("vscode"));
var ft = class extends J {
  constructor(t, e = !1) {
    super(t, e);
  }
  async downloadUserProgram(t, e, o, s, n = !1) {
    switch (this._device) {
      case i.Device.Brain:
        if (this._bootMode !== I.BootMode.app)
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} running ${this._bootMode} bootloader`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        let a = await this._vexcom.downloadUserProgram(
          t,
          e,
          s.fsPath,
          o,
          n,
          !1
        );
        return I._toCommandResponse(a);
      case i.Device.Unknown:
      default:
        return {
          command: x.CommandID.downloadUserProgram,
          details: "Unknown Device Connected",
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
    }
  }
  async systemUpdate(t, e = !1) {
    let o = {
        location: As.ProgressLocation.Notification,
        title: "Vexos Update:",
        cancellable: !1,
      },
      s = await this._handleProgress(
        () => this._vexcom.sytemUpdate(t.fsPath, e),
        o
      );
    return I._toCommandResponse(s);
  }
  get needsVexosUpdate() {
    return this._needsVexosUpdate;
  }
  set needsVexosUpdate(t) {
    this._needsVexosUpdate = t;
  }
};
var io = L(require("vscode"));
var We = class extends J {
  constructor(e, o = !1, s) {
    super(e, o, s);
    this._needsRadioUpdate = !1;
    this._needsUsbUpDate = !1;
  }
  async downloadUserProgram(e, o, s, n, a = !1) {
    switch (this._device) {
      case i.Device.Controller:
        if (!this._systemInfo?.controller?.flags)
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} No Radio Status`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        if (
          (Number(this._systemInfo?.controller?.flags) & 2) !== 2 &&
          this._systemInfo?.brain === void 0
        )
          return {
            command: x.CommandID.downloadUserProgram,
            details: `${this._platform} ${this._device} Not Linked to brain`,
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
        let r = {
          location: io.ProgressLocation.Notification,
          title: "Program Download:",
          cancellable: !1,
        };
        if (
          this._platform === i.Platform.EXP ||
          this._platform === i.Platform.IQ2
        ) {
          let l = await this._handleProgress(
            () => this._vexcom.downloadUserProgram(e, o, n.fsPath, s, a, !0),
            r
          );
          return I._toCommandResponse(l);
        } else
          return {
            command: x.CommandID.downloadUserProgram,
            details: "Unknown Device Connected ",
            json: "{}",
            statusCode: x.ExitCode.vexError,
          };
      case i.Device.Unknown:
      default:
        return {
          command: x.CommandID.downloadUserProgram,
          details: "Unknown Device Connected ",
          json: "{}",
          statusCode: x.ExitCode.vexError,
        };
    }
  }
  async controllerUsbUpdate(e) {
    let o = {
        location: io.ProgressLocation.Notification,
        title: `${this.platform} ${this.device} Usb Update: `,
        cancellable: !1,
      },
      s = await this._handleProgress(async () => {
        this._progress?.report({
          increment: 50,
          message: "50 %",
        });
        let n = await this._vexcom.controllerAtmelFirmwareUpdate(e.fsPath);
        return (
          n.exitCode === x.ExitCode.vexSucess &&
            ((this._needsUsbUpDate = !1),
            this._progress?.report({
              increment: 50,
              message: "100 %",
            }),
            await i.Utils.asyncSleep(100)),
          n
        );
      }, o);
    return I._toCommandResponse(s);
  }
  async controllerRadioUpdate(e) {
    let o = {
        location: io.ProgressLocation.Notification,
        title: `${this.platform} ${this.device} Radio Update: `,
        cancellable: !1,
      },
      s = await this._handleProgress(
        () => this._vexcom.controllerRadioFirmwareUpdate(e.fsPath),
        o
      );
    return (
      s.exitCode === x.ExitCode.vexSucess && (this._needsRadioUpdate = !1),
      I._toCommandResponse(s)
    );
  }
  async controllerUpdate(e) {
    let o = {
      location: io.ProgressLocation.Notification,
      title: `${this.platform} ${this.device} Update: `,
      cancellable: !1,
    };
    return (
      await this.controllerRadioUpdate(e), await this.controllerUsbUpdate(e)
    );
  }
  static async controllerUsbUpdate(e) {
    let o = i.Extension.getVexcomUri(i.Extension.context),
      s = new x(o.fsPath, "", { active: !1, maxCmds: 0 }),
      n = {
        location: io.ProgressLocation.Notification,
        title: "Controller Usb Update:",
        cancellable: !1,
      },
      a = await s.controllerAtmelFirmwareUpdate(e.fsPath);
    return I._toCommandResponse(a);
  }
  async uploadEventLog() {
    let e = await super._isControllerRadioLinked();
    return e
      ? ((e.command = x.CommandID.uploadEventLog), e)
      : await super.uploadEventLog();
  }
  get needsRadioUpdate() {
    return this._needsRadioUpdate;
  }
  set needsRadioUpdate(e) {
    this._needsRadioUpdate = e;
  }
  get needsUsbUpdate() {
    return this._needsUsbUpDate;
  }
  set needsUsbUpdate(e) {
    this._needsUsbUpDate = e;
  }
  get needsVexosUpdate() {
    return (
      (this._needsVexosUpdate = this._needsUsbUpDate && this._needsRadioUpdate),
      this._needsUsbUpDate && this._needsRadioUpdate
    );
  }
  set needsVexosUpdate(e) {
    this._needsVexosUpdate = e;
  }
};
var Ls = L(require("vscode"));
var Be = class extends I {
  constructor(e) {
    super();
    this._vexcomDataHolder = "";
    this._dataResultArr = [];
    this._vid = "";
    this._pid = "";
    (this._bootMode = e.bootMode),
      (this._platform = e.platform),
      (this._device = e.device),
      (this._vid = e.vid),
      (this._pid = e.pid);
    let o = i.Extension.getVexcomUri(i.Extension.context);
    (this._vexcom = new x(o.fsPath, "", { active: !0, maxCmds: 0 })),
      this._vexcom.on("Data", (s, n) => {
        this._onVexcomDataRecieved(this, s, n);
      }),
      this._vexcom.on("Error", (s, n) => {
        this._onVexcomErrorRecieved(this, s, n);
      }),
      this._vexcom.on("Exit", (s, n) => {
        this._onVexcomExitRecieved(this, s, n);
      });
  }
  get activeCommand() {
    return this._vexcom.activeCommand.cmdID;
  }
  static isTypeOf(e) {
    return e instanceof Be;
  }
  get pid() {
    return this._pid;
  }
  get vid() {
    return this._vid;
  }
  async _handleProgress(e, o) {
    let s,
      n = async (a, r) => (
        a?.report({ increment: 0, message: "preparing..." }), await e()
      );
    {
      let a = Ls.window.withProgress(o, async (r, c) => {
        this._progress ||
          ((this._lastProgress = 0),
          (this._progress = r),
          (s = n(r, c)),
          await s,
          (this._progress = void 0));
      });
    }
    return s;
  }
  _onVexcomDataRecieved(e, o, s) {
    switch (o) {
      case x.CommandID.systemStatus:
      case x.CommandID.systemInfo:
        e._vexcomDataHolder += s;
        break;
      case x.CommandID.controllerRadioUpdate:
      case x.CommandID.controllerUsbUpdate:
      case x.CommandID.downloadUserProgram:
      case x.CommandID.downloadPythonVM:
      case x.CommandID.systemUpdate:
        let n;
        try {
          n = JSON.parse(s) ? JSON.parse(s) : "";
        } catch {
          return;
        }
        let a = n.percent - this._lastProgress;
        (this._lastProgress = n.percent),
          this._progress?.report({
            increment: a,
            message: `${n.action.toUpperCase()}:${n.phase.toUpperCase()} ${
              n.percent
            }%`,
          });
        break;
    }
  }
  _onVexcomErrorRecieved(e, o, s) {}
  _onVexcomExitRecieved(e, o, s) {
    switch (o) {
      case x.CommandID.systemStatus:
      case x.CommandID.systemInfo:
        e._dataResultArr.push(e._vexcomDataHolder), (e._vexcomDataHolder = "");
        break;
    }
  }
  static toCommandResponse(e, o) {
    return {
      command: e?.cmdID ? e.cmdID : x.CommandID.unknown,
      details: `${x.getErrorCodeDetails(e.exitCode)} ${e.stderr} | ${e.cmdStr}`,
      statusCode: e.exitCode,
      json: o || "{}",
    };
  }
};
var Lt = class extends Be {
  constructor(t) {
    super(t);
  }
  async recover() {
    let t = await this._vexcom.recoverFromDFU(this._platform);
    return I._toCommandResponse(t);
  }
};
var Ot = class extends Be {
  constructor(t) {
    super(t);
  }
  async recover() {
    let t = await this._vexcom.recoverFromDFU(this._platform);
    return I._toCommandResponse(t);
  }
};
var Os = L(require("vscode"));
var St = class extends Be {
  constructor(t) {
    super(t);
  }
  async recover(t) {
    let e = await this._vexcom.recoverFromDFU(this._platform);
    return I._toCommandResponse(e);
  }
  async controllerUsbUpdate(t) {
    let e = {
        location: Os.ProgressLocation.Notification,
        title: "Controller Usb Update: ",
        cancellable: !1,
      },
      o = await this._vexcom.controllerAtmelFirmwareUpdate(t.fsPath);
    return I._toCommandResponse(o);
  }
};
var Bs = L(require("vscode"));
var Et = class extends Be {
  constructor(t) {
    super(t);
  }
  async recover(t) {
    let e = await this._vexcom.controllerAtmelFirmwareUpdate(t.fsPath);
    return I._toCommandResponse(e);
  }
  async controllerUsbUpdate(t) {
    let e = {
        location: Bs.ProgressLocation.Notification,
        title: "Controller Usb Update: ",
        cancellable: !1,
      },
      o = await this._vexcom.controllerAtmelFirmwareUpdate(t.fsPath);
    return I._toCommandResponse(o);
  }
};
var qt = L(require("vscode"));
var Fs = L(require("vscode"));
var ro = class extends I {
  constructor(e, o = !1, s) {
    super();
    this._vexcomDataHolder = "";
    this._dataResultArr = [];
    (this._vexcomDataHolder = ""),
      (this._dataResultArr = []),
      (this._platform = e.platform),
      (this._device = e.device),
      (this._name = e.robotName),
      (this._communicationPath = e.communication),
      (this._userPath = e.user),
      (this._id = e.id),
      (this._systemInfoJSON = e.json),
      (this._bootMode = I.BootMode.app),
      (this._userPort = new At(this._userPath));
  }
  async _handleProgress(e, o) {
    let s,
      n = async (a, r) => (
        a?.report({ increment: 0, message: "preparing..." }), await e()
      );
    {
      let a = Fs.window.withProgress(o, async (r, c) => {
        this._progress ||
          ((this._lastProgress = 0),
          (this._progress = r),
          (s = n(r, c)),
          await s,
          (this._progress = void 0));
      });
    }
    return s;
  }
  get name() {
    return this._name;
  }
  get bootMode() {
    return this._bootMode;
  }
  get platform() {
    return this._platform;
  }
  get device() {
    return this._device;
  }
  get json() {
    return this._systemInfoJSON;
  }
  get systemInfo() {
    return this._systemInfo;
  }
  get userPort() {
    return this?._userPort;
  }
};
var ns = L(require("path"));
var _e = class extends ro {
  constructor(e, o = !1, s) {
    super(e, o, s);
    this._dataHolder = "";
    this._appUpdateList = [];
    this._aliveFailedAttempts = 0;
    this._vexupdateMissing = !1;
    this._fileDownloadInProgress = !1;
    (this._communicationPort = new At(this._communicationPath, 115200)),
      this._communicationPort.serialPort.removeAllListeners(),
      this._communicationPort.registerCallback(
        "OnRecieveData",
        this._onComsDataRecievedHandle
      ),
      (this._isAlive = !1),
      (this._ssidChanged = !1),
      (this._passwordChanged = !1),
      (this._needsUpdate = !1),
      (this._dataHolder = ""),
      (this._vexaicomms = new F(this._communicationPort.serialPort));
  }
  async systemUpdate(e, o = !1) {
    let s = {
      location: qt.ProgressLocation.Notification,
      title: "Vexos Update:",
      cancellable: !1,
    };
  }
  get user() {
    return this._userPath;
  }
  get communication() {
    return this._communicationPath;
  }
  get comsPort() {
    return this?._communicationPort;
  }
  get needsUpdate() {
    return this?._needsUpdate;
  }
  set needsUpdate(e) {
    this._needsUpdate = e;
  }
  async checkAlive() {
    this._communicationPort.serialPort.flush();
    let e = await this._vexaicomms.sendAlive();
    return (
      e.exitCode === 0
        ? ((this._isAlive = !0),
          (this._vexupdateMissing = !1),
          (this._aliveFailedAttempts = 0))
        : (this._aliveFailedAttempts++,
          this._aliveFailedAttempts > 10 && (this._vexupdateMissing = !0)),
      i.Utils._toCommandResponse(e)
    );
  }
  async setSSID(e) {
    let o = this._checkDeviceVexUpdate(F.Commands.setSSID);
    if (o) return o;
    let s = await this._vexaicomms.setAccessPointSSID(e);
    return (
      s.exitCode === F.StatusCodes.ack && (this._ssidChanged = !0),
      i.Utils._toCommandResponse(s)
    );
  }
  async setPassword(e) {
    let o = this._checkDeviceVexUpdate(F.Commands.setPassword);
    if (o) return o;
    let s = await this._vexaicomms.setAccessPointPassword(e);
    return (
      s.exitCode === F.StatusCodes.ack && (this._passwordChanged = !0),
      i.Utils._toCommandResponse(s)
    );
  }
  async getDeviceInfo(e) {
    let o = this._checkDeviceVexUpdate(F.Commands.deviceInfo);
    if (o) return o;
    let s = ["aiwebdashboard", "vexupdate", "aiservice"];
    if (this._fileDownloadInProgress)
      return {
        command: F.Commands.deviceInfo,
        details: F.vexaiErrorMap.get(F.StatusCodes.downloadCommandActive),
        json: "",
        statusCode: F.StatusCodes.downloadCommandActive,
      };
    let n = await this._vexaicomms.getDeviceInfo(e || s),
      a = new TextDecoder().decode(n.data),
      r;
    try {
      (r = JSON.parse(a)),
        (r.info = JSON.parse(Buffer.from(r.info, "base64").toString()));
    } catch (c) {
      console.log(c);
    }
    return (
      (this._name = r.info.device.name),
      (this._id = r.info.device.id),
      (this._systemInfo = r.info),
      (super._systemInfoJSON = r.info.toString()),
      i.Utils._toCommandResponse(n)
    );
  }
  async checkElevate() {
    let e = this._checkDeviceVexUpdate(F.Commands.checkElevate);
    if (e) return e;
    let o = await this._vexaicomms.getCheckElevateCMD();
    return i.Utils._toCommandResponse(o);
  }
  async elevate() {
    let e = this._checkDeviceVexUpdate(F.Commands.checkElevate);
    if (e) return e;
    let o = await this._vexaicomms.getElevateCMD();
    return i.Utils._toCommandResponse(o);
  }
  checkDirCMD(e) {}
  async downloadApp(e, o) {
    let s = this._checkDeviceVexUpdate(F.Commands.run);
    if (s) return s;
    this._fileDownloadInProgress = !0;
    let n;
    await qt.window.withProgress(
      {
        cancellable: !1,
        title: `VEX AI File Download: ${ns.basename(e.fsPath)}`,
        location: qt.ProgressLocation.Notification,
      },
      async (r, c) => {
        (n = this._vexaicomms.downloadApplication(e.fsPath, o?.fsPath, (l) => {
          r.report(l);
        })),
          await n,
          console.log(n);
      }
    );
    let a = await n;
    return (this._fileDownloadInProgress = !1), i.Utils._toCommandResponse(a);
  }
  async installApp(e) {
    let o = this._checkDeviceVexUpdate(F.Commands.run);
    if (o) return o;
    let s = !0,
      n,
      a;
    qt.window.withProgress(
      {
        cancellable: !1,
        title: `VEX AI Install App: ${ns.basename(e.fsPath)}`,
        location: qt.ProgressLocation.Notification,
      },
      async (c, l) => {
        (n = this._vexaicomms.installAppCMD(e.path)),
          (a = await n),
          (s = !1),
          console.log(a);
      }
    );
    let r = !1;
    for (; s; ) {
      if (!this._communicationPort.isOpen) {
        (r = !0),
          (s = !1),
          gt.activeCmd.internalResolve(
            `{command:"${F.Commands.run}",response:"${F.StatusCodes.nack}", exitcode:"${F.StatusCodes.port_not_open}"}`
          );
        break;
      }
      await i.Utils.asyncSleep(500);
    }
    return i.Utils._toCommandResponse(a);
  }
  async removeApp(e) {
    let o = this._checkDeviceVexUpdate(F.Commands.run);
    if (o) return o;
    let s = await this._vexaicomms.removeAppCMD(e);
    return i.Utils._toCommandResponse(s);
  }
  async systemCtlService(e, o) {
    let s = this._checkDeviceVexUpdate(F.Commands.run);
    if (s) return s;
    let n = await this._vexaicomms.restartServiceCMD(e, o);
    return i.Utils._toCommandResponse(n);
  }
  async clear() {
    let e = this._checkDeviceVexUpdate(F.Commands.run);
    if (e) return e;
    let o = await this._vexaicomms.clearRxBufferCMD();
    return i.Utils._toCommandResponse(o);
  }
  async resetTerminal() {
    let e = this._checkDeviceVexUpdate(F.Commands.run);
    if (e) return e;
    let o = await this._vexaicomms.restartTerminal();
    return i.Utils._toCommandResponse(o);
  }
  async removeFile(e) {
    let o = await this._vexaicomms.rmCMD(e);
    return i.Utils._toCommandResponse(o);
  }
  async sendRunCMD(e, o = "/") {}
  _onComsDataRecievedHandle(e) {
    if (!e) return;
    this._dataHolder === void 0 && (this._dataHolder = "");
    let o = new TextDecoder().decode(e);
    if (!o.includes(``)) {
      this._dataHolder += o;
      return;
    }
    let s = o.split(``),
      n = this._dataHolder + s[0];
    this._dataHolder = s[1];
    let a = JSON.parse(n);
    if (gt.activeCmd.cmdID === a.command) {
      a.command === F.Commands.run && console.log(a);
      let r = a.response === "ACK" ? F.StatusCodes.ack : F.StatusCodes.nack,
        c = F.getErrorCodeDetails(r),
        l = {
          vexaicommsI: "",
          cmdID: a.command,
          cmdStr: "",
          data: new TextEncoder().encode(n),
          details: c,
          exitCode: r,
        };
      if (r === F.StatusCodes.ack) l.details = `${a.response}`;
      else if (a?.error) {
        let d = Buffer.from(a.error, "base64").toString();
        if (F.Commands.run === a.command) {
          let m = Buffer.from(a.stderr, "base64").toString();
          l.details += ` ${a.response} (${d} ${m}) `;
        } else l.details += ` ${a.response} (${d}) `;
      }
      i.DEBUG, gt.activeCmd.internalResolve(l);
      return;
    }
  }
  _checkDeviceVexUpdate(e) {
    let o = {
      command: e,
      details: "",
      json: "{}",
      statusCode: F.StatusCodes.downloadCommandActive,
    };
    if (this._vexupdateMissing)
      return (
        (o.statusCode = F.StatusCodes.vexupdateMissing),
        (o.details = F.getErrorCodeDetails(o.statusCode)),
        o
      );
    if (!this._isAlive)
      return (
        (o.statusCode = F.StatusCodes.deviceNotAlive),
        (o.details = F.getErrorCodeDetails(o.statusCode)),
        o
      );
  }
  get isAlive() {
    return this._isAlive;
  }
  get isVexupdateMissing() {
    return this._vexupdateMissing;
  }
  get ssidChanged() {
    return this._ssidChanged;
  }
  get passwordChanged() {
    return this._passwordChanged;
  }
  get updateList() {
    return this._appUpdateList;
  }
  set updateList(e) {
    this._appUpdateList = e;
  }
  get ssid() {
    return this._systemInfo?.device?.name ? this._systemInfo.device.name : "";
  }
};
var ho = class {
  static createDevice(t) {
    switch (`${t.platform}-${t.device}-${t.bootMode}`) {
      case `${i.Platform.V5}-${i.Device.Brain}-${I.BootMode.app}`:
        return new Ct(t);
      case `${i.Platform.EXP}-${i.Device.Brain}-${I.BootMode.app}`:
      case `${i.Platform.EXP}-${i.Device.Brain}-${I.BootMode.rom}`:
      case `${i.Platform.EXP}-${i.Device.Brain}-${I.BootMode.ram}`:
        return new vt(t);
      case `${i.Platform.IQ2}-${i.Device.Brain}-${I.BootMode.app}`:
      case `${i.Platform.IQ2}-${i.Device.Brain}-${I.BootMode.rom}`:
      case `${i.Platform.IQ2}-${i.Device.Brain}-${I.BootMode.ram}`:
        return new ft(t);
      case `${i.Platform.V5}-${i.Device.Controller}-${I.BootMode.app}`:
        return new Je(t);
      case `${i.Platform.EXP}-${i.Device.Controller}-${I.BootMode.app}`:
      case `${i.Platform.EXP}-${i.Device.Controller}-${I.BootMode.rom}`:
        return new et(t);
      case `${i.Platform.IQ2}-${i.Device.Controller}-${I.BootMode.app}`:
      case `${i.Platform.IQ2}-${i.Device.Controller}-${I.BootMode.rom}`:
        return new We(t);
      case `${i.Platform.AI}-${i.Device.Camera_3D}-${I.BootMode.app}`:
        return new _e(t);
      default:
        return;
    }
  }
};
var Xs = L(require("vscode"));
var no = class extends I {
  constructor(e) {
    super();
    this._vexcomDataHolder = "";
    this._dataResultArr = [];
    (this._vexcomDataHolder = ""),
      (this._dataResultArr = []),
      (this._platform = e.platform),
      (this._device = e.device),
      (this._id = e.id),
      (this._bootMode = e.bootMode),
      (this._vid = e.vid),
      (this._pid = e.pid);
  }
  async _handleProgress(e, o) {
    let s,
      n = async (a, r) => (
        a?.report({
          increment: 0,
          message: "preparing . . . ",
        }),
        await e()
      );
    {
      let a = Xs.window.withProgress(o, async (r, c) => {
        this._progress ||
          ((this._lastProgress = 0),
          (this._progress = r),
          (s = n(r, c)),
          await s,
          (this._progress = void 0));
      });
    }
    return s;
  }
  get name() {
    return this._name;
  }
  get bootMode() {
    return this._bootMode;
  }
  get platform() {
    return this._platform;
  }
  get device() {
    return this._device;
  }
  get json() {
    return this._systemInfoJSON;
  }
  get systemInfo() {
    return this._systemInfo;
  }
  get vid() {
    return this._vid;
  }
  get pid() {
    return this._pid;
  }
};
var Bt = class extends no {
  constructor(t) {
    super(t);
  }
  async deviceUpdate(t) {
    let e = await this._uuu.flash(t.fsPath);
    return i.Utils._toCommandResponse(e);
  }
  on(t, e) {
    switch (t) {
      case "Data":
        this._uuu.on("Data", e);
        break;
      case "Progress":
        this._uuu.on("Progress", e);
        break;
      case "Error":
        this._uuu.on("Error", e);
        break;
      case "Exit":
        this._uuu.on("Exit", e);
        break;
    }
  }
};
var xo = class {
  static createDevice(t) {
    switch (`${t.platform}-${t.device}-${I.BootMode.dfu}`) {
      case `${i.Platform.EXP}-${i.Device.Brain}-${I.BootMode.dfu}`:
        return new Lt(t);
      case `${i.Platform.IQ2}-${i.Device.Brain}-${I.BootMode.dfu}`:
        return new Ot(t);
      case `${i.Platform.EXP}-${i.Device.Controller}-${I.BootMode.dfu}`:
        return new St(t);
      case `${i.Platform.IQ2}-${i.Device.Controller}-${I.BootMode.dfu}`:
        return new Et(t);
      case `${i.Platform.AI}-${i.Device.Camera_3D}-${I.BootMode.dfu}`:
      case `${i.Platform.AI}-${i.Device.Camera_3D}-${I.BootMode.ram}`:
        return new Bt(t);
      default:
        return;
    }
  }
};
var Ye = L(require("vscode")),
  Hs = require("serialport"),
  as = L(require("child_process")),
  bo = L(require("path")),
  cs = L(require("os")),
  B = class {
    constructor(t, e) {
      this._maxDeviceConnects = 2;
      this._maxDeviceDisconnects = 2;
      this._dfuConnectCounter = 0;
      this._dfuDisconnectCounter = 0;
      this._detectLoopInLock = !1;
      this._deviceDetectionLock = !1;
      this._deviceDFUDetectionLock = !1;
      (B._context = t),
        (this._activeDeviceList = []),
        (this._activeDFUDeviceList = []),
        (B._logCB = e),
        B._logHandler("Starting");
    }
    async checkSystemVEXOS(t) {
      if (!(t instanceof J) || !(t instanceof J)) return;
      B._logHandler("Checking Device Vexos against Local Vexos-------------");
      let e = Ye.Uri.joinPath(B._context.globalStorageUri, "vexos"),
        o = (await i.Extension.ResourceManager.getVEXosVersions(t.platform, e))
          .json,
        s = JSON.parse(o),
        n = JSON.parse(t.json),
        a;
      n.v5 && (a = n.v5.brain.vexos),
        n.exp &&
          (t.bootMode === I.BootMode.app
            ? (a = n.exp.brain.vexos)
            : (t.bootMode === I.BootMode.ram ||
                t.bootMode === I.BootMode.rom) &&
              (a = n.exp.brain.version)),
        n.iq2 &&
          (t.bootMode === I.BootMode.app
            ? (a = n.iq2.brain.vexos)
            : (t.bootMode === I.BootMode.ram ||
                t.bootMode === I.BootMode.rom) &&
              (a = n.iq2.brain.version));
      let r = i.Utils.vexos.toVersion(a).split(".").join("_"),
        c = `VEXOS_${t.platform}_${r}`,
        l = s.online.latest !== "",
        d = s.local.latest !== "",
        m = "",
        w = !1,
        b,
        C = {
          command: "check vexos",
          details: "",
          json: "",
          statusCode: 0,
        };
      if (l)
        return (
          (b = i.Utils.vexos.getLatestVEXosVersion([
            c,
            s.online.latest,
            s.local.latest,
          ])),
          b !== c || t.bootMode !== I.BootMode.app || w
            ? (B._logHandler(
                `Vexos update available: Online-${s.online.latest} Local-${
                  s.local.latest
                } System-${i.Utils.vexos.fileNameToVersion(c)} BootMode: ${
                  t.bootMode
                }`
              ),
              (m = `Vexos update available: ${i.Utils.vexos.fileNameToVersion(
                b
              )}`),
              (C.details = m),
              (C.statusCode = 1),
              C)
            : Number(n?.v5?.brain?.flags) & 65536
            ? (B._logHandler(
                `Vexos update available: Assets Invalid, Online-${
                  s.online.latest
                } System-${i.Utils.vexos.fileNameToVersion(c)} BootMode: ${
                  t.bootMode
                }`
              ),
              (m = `Vexos update available: ${i.Utils.vexos.fileNameToVersion(
                b
              )}`),
              (C.details = m),
              (C.statusCode = 1),
              C)
            : (B._logHandler(
                `VEXOS Version: Online:${s.online.latest} System:${c}`
              ),
              B._logHandler("VEXOS - Up To Date"),
              (C.details = "VEXOS up to date"),
              (C.statusCode = 0),
              C)
        );
      if (d)
        return (
          (b = i.Utils.vexos.getLatestVEXosVersion([c, s.local.latest])),
          b !== c || t.bootMode !== I.BootMode.app
            ? (B._logHandler(
                `Vexos update available: ${i.Utils.vexos.fileNameToVersion(
                  c
                )} BootMode: ${t.bootMode}`
              ),
              (m = `Vexos update available: ${i.Utils.vexos.fileNameToVersion(
                b
              )}`),
              (C.details = m),
              (C.statusCode = 1),
              C)
            : (B._logHandler(
                `VEXOS Version @: Online:${s.online.latest} System:${c}`
              ),
              B._logHandler("VEXOS - Up To Date"),
              (C.details = "VEXOS up to date"),
              (C.statusCode = 0),
              C)
        );
      throw new Error(
        "No Internet connection and no vexos availiable at current home directory"
      );
      B._logHandler(`VEXOS Check Result: ${m}`);
    }
    async checkControllerVEXOS(t) {
      if (!(t instanceof We) && !(t instanceof et)) return;
      B._logHandler("Checking Device Vexos against Local Vexos-------------");
      let e = Ye.Uri.joinPath(B._context.globalStorageUri, "vexos"),
        o = (await i.Extension.ResourceManager.getVEXosVersions(t.platform, e))
          .json,
        s = JSON.parse(o),
        n = JSON.parse(t.json),
        a = s.online.latest !== "",
        r = s.local.latest !== "",
        c = "",
        l = !1,
        d,
        m,
        w = {
          command: "check controller vexos",
          details: "",
          json: "",
          statusCode: 0,
        },
        b = await i.Extension.ResourceManager.getLatestVEXosManifest(
          t.platform,
          e
        ),
        C = JSON.parse(b.json),
        E,
        T,
        O,
        f;
      t.bootMode === I.BootMode.app
        ? ((E = i.Utils.vexos.toVersion(t.vexComSystemInfo?.controller?.version)
            ? i.Utils.vexos.toVersion(t?.vexComSystemInfo?.controller?.version)
            : ""),
          (T = i.Utils.vexos.toVersion(t.vexComSystemInfo?.controller?.atmel)
            ? i.Utils.vexos.toVersion(t?.vexComSystemInfo?.controller?.atmel)
            : ""),
          (O = C.ctrl.cdc.version),
          (f = C.ctrl.radio.version))
        : ((E = ""),
          (T = i.Utils.vexos.toVersion(
            t.vexComSystemInfo?.controller_boot?.atmel
          )
            ? i.Utils.vexos.toVersion(
                t.vexComSystemInfo?.controller_boot?.atmel
              )
            : ""),
          (O = C.ctrl.cdc.version),
          (f = C.ctrl.radio.version));
      let k;
      console.log(t.vexComSystemInfo),
        (d = i.Utils.vexos.getLatestControllerVersion([E, f])),
        (m = i.Utils.vexos.getLatestControllerVersion([T, O]));
      let z = !1,
        Z = !1;
      return (
        d !== E || l
          ? (B._logHandler(
              `${t.platform} ${t.device} VEXOS update available:${E} -> ${f}`
            ),
            (c = `${t.platform} ${t.device} VEXOS update available:${C.version}`),
            (w.details = c),
            (w.statusCode = 1),
            (z = !0),
            (t.needsRadioUpdate = !0))
          : (z = !1),
        m !== T || l
          ? (B._logHandler(
              `${t.platform} ${t.device} USB update available: ${T} -> ${O}`
            ),
            (c = `${t.platform} ${t.device} VEXOS update available:${C.version}`),
            (w.details = c),
            (w.statusCode = 1),
            (Z = !0),
            (t.needsUsbUpdate = !0))
          : (Z = !1),
        B._logHandler("VEXOS - Up To Date"),
        w.statusCode || (w.details = "VEXOS up to date"),
        (w.json = JSON.stringify({
          usb: Z,
          radio: z,
        })),
        w
      );
    }
    async checkVEXaiVersion(t, e = !1) {
      B._logHandler(
        "Checking Device Version against Local VEXai image-------------"
      );
      let o = Ye.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.aiCameraHomeID,
            Ye.ConfigurationTarget.Global
          )
          .toString(),
        s = JSON.parse(
          (
            await i.Extension.ResourceManager.getLatestVEXaiManifest(
              Ye.Uri.joinPath(Ye.Uri.file(o), "3d", "images")
            )
          ).json
        ),
        n = !!s.online.catalog,
        a = !!s.local.catalog,
        r = [],
        c = "",
        l = "",
        d = t.systemInfo.device?.version ? t.systemInfo.device?.version : "",
        m = {
          command: "check vexai 3d camera version",
          details: "",
          json: "",
          statusCode: 0,
        },
        w = (b, C) => (b > C ? -1 : b < C ? 1 : 0);
      if (n)
        return (
          (c = [
            d,
            s.online.latest.split("_")[1],
            s.local.latest.split("_")[1],
          ].sort(w)[0]),
          c !== d || t.bootMode !== I.BootMode.app || e
            ? (B._logHandler(
                `VEXai Image update available: Online-${s.online.latest} Local-${s.local.latest} Device-${d} BootMode: ${t.bootMode}`
              ),
              (l = `VEXai Image update available: ${i.Utils.vexos.fileNameToVersion(
                c
              )}`),
              (m.details = l),
              (m.statusCode = 1),
              m)
            : (B._logHandler(
                `VEXai Image Version: Online:${s.online.latest} Device:${d}`
              ),
              B._logHandler("VEXai Image - Up To Date"),
              (m.details = "VEXai Image up to date"),
              (m.statusCode = 0),
              m)
        );
      if (a)
        return (
          (c = [d, s.local.latest].sort(w)[0]),
          c !== d || t.bootMode !== I.BootMode.app
            ? (B._logHandler(
                `VEXai Image update available: ${i.Utils.vexos.fileNameToVersion(
                  d
                )} BootMode: ${t.bootMode}`
              ),
              (l = `VEXai Image update available: ${i.Utils.vexos.fileNameToVersion(
                c
              )}`),
              (m.details = l),
              (m.statusCode = 1),
              m)
            : (B._logHandler(
                `VEXai Image Version @: Online:${s.online.latest} Device:${d}`
              ),
              B._logHandler("VEXai Image - Up To Date"),
              (m.details = "VEXai Image up to date"),
              (m.statusCode = 0),
              m)
        );
      throw new Error(
        "No Internet connection and no vexos availiable at current home directory"
      );
    }
    async checkVEXaiApps(t, e = !1) {
      B._logHandler(
        "Checking Device Application against Local Vexos-------------"
      );
      let o = Ye.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.aiCameraHomeID,
            Ye.ConfigurationTarget.Global
          )
          .toString(),
        s = JSON.parse(
          (
            await i.Extension.ResourceManager.getVEXaiAppListVersions(
              Ye.Uri.file(o)
            )
          ).json
        ),
        n = !!s.online.apps.length,
        a = !!s.local.apps.length,
        r = [];
      if (n) r = s.online.apps;
      else if (a) r = s.local.apps;
      else
        throw new Error(
          "No Internet connection and no vexos availiable at current home directory"
        );
      r.forEach(async (c) => {
        console.log(c);
        let l = await this.checkVEXaiAppVersion(t, c, n, a);
        l.statusCode === 1 && t.updateList.push(c), console.log(l);
      });
    }
    async checkVEXaiAppVersion(t, e, o, s, n = !1) {
      let a;
      t.systemInfo.apps.forEach((b) => {
        b.Package === e && (a = b);
      });
      let r = {
          command: "",
          details: "",
          json: "",
          statusCode: 0,
        },
        c = Ye.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.aiCameraHomeID,
            Ye.ConfigurationTarget.Global
          )
          .toString(),
        l = JSON.parse(
          (
            await i.Extension.ResourceManager.getVEXaiAppVersions(
              e,
              Ye.Uri.file(c)
            )
          ).json
        ),
        d = `${a.Package}_${a.Version}`,
        m = `${l.online.latest.split("-")[0]}`,
        w = l.local.latest.split("-")[0];
      if (o) {
        let b = [d, m, w].sort((E, T) => {
            let O = E.split("_"),
              f = T.split("_"),
              k = O[1].split("."),
              z = f[1].split("."),
              Z = (ye, se) => (ye > se ? -1 : ye < se ? 1 : 0),
              S = Z(parseInt(k[0]), parseInt(z[0]));
            if (S !== 0) return S;
            let W = Z(parseInt(k[1]), parseInt(z[1]));
            if (W !== 0) return W;
            let V = Z(parseInt(k[2]), parseInt(z[2]));
            if (V !== 0) return V;
            let X = Z(k[3], z[4]);
            return X !== 0 ? X : 0;
          }),
          C = b[0];
        if ((console.log(b), C !== d || t.bootMode !== I.BootMode.app || n)) {
          B._logHandler(
            `VEXai App update available: Online-${l.online.latest} Local-${l.local.latest} System-${d} BootMode: ${t.bootMode}`
          );
          let E = `VEXai App update available: ${i.Utils.vexos.fileNameToVersion(
            C
          )}`;
          return (r.details = E), (r.statusCode = 1), r;
        } else
          return (
            B._logHandler(
              `VEXai App  Version: Online:${l.online.latest} System:${d}`
            ),
            B._logHandler("VEXai App  - Up To Date"),
            (r.details = "VEXai up to date"),
            (r.statusCode = 0),
            r
          );
      } else if (s) {
        let b = [d[0], m, w].sort((C, E) => (C > E ? -1 : C < E ? 1 : 0))[0];
        if (b !== d || t.bootMode !== I.BootMode.app) {
          B._logHandler(
            `VEXai App update available: ${i.Utils.vexos.fileNameToVersion(
              d
            )} BootMode: ${t.bootMode}`
          );
          let C = `VEXai App update available: ${i.Utils.vexos.fileNameToVersion(
            b
          )}`;
          return (r.details = C), (r.statusCode = 1), r;
        } else
          return (
            B._logHandler(
              `VEXai App  Version @: Online:${l.online.latest} System:${d}`
            ),
            B._logHandler("VEXai App  - Up To Date"),
            (r.details = "VEXai up to date"),
            (r.statusCode = 0),
            r
          );
      } else
        throw new Error(
          "No Internet connection and no vexos availiable at current home directory"
        );
      console.log(s, o);
    }
    static async getVEXDeviceList(t) {
      let e = await Hs.SerialPort.list();
      B._serialPortIOList = e;
      let o = this.filterbyType(e, "User", t),
        s = this.filterbyType(e, "Communication", t),
        n = cs.type(),
        a = [];
      return (
        s.forEach((r) => {
          if (r.productId === this._v5ControllerPid) {
            let c = this.getDeviceTypeFromPID(r.productId),
              l = {
                platform: c.platform,
                device: c.device,
                bootMode: I.BootMode.unknown,
                user: "",
                communication: r.path,
                robotName: "",
                teamNumber: "",
                id: "",
                json: "",
              };
            a.some(
              (d) => l.communication === d.communication || l.user === d.user
            ) || a.push(l);
            return;
          }
          o.forEach((c) => {
            if (this.comparePortByPlatform(n, c, r)) {
              let d = this.getDeviceTypeFromPID(r.productId),
                m = {
                  platform: d.platform,
                  device: d.device,
                  user: c.path,
                  bootMode: I.BootMode.unknown,
                  communication: r.path,
                  robotName: "",
                  teamNumber: "",
                  id: "",
                  json: "",
                };
              a.some(
                (w) => m.communication === w.communication || m.user === w.user
              ) || a.push(m);
            }
          });
        }),
        o.forEach((r) => {
          if (r.productId === this._vexAI3DCameraPid) {
            let c = this.getDeviceTypeFromPID(r.productId),
              l = {
                platform: c.platform,
                device: c.device,
                bootMode: I.BootMode.unknown,
                user: r.path,
                communication: "",
                robotName: "",
                teamNumber: "",
                id: "",
                json: "",
              };
            a.some(
              (d) => l.communication === d.communication || l.user === d.user
            ) || a.push(l);
            return;
          }
        }),
        a.sort(this._sortListCB),
        a
      );
    }
    static async getVEXDfuDeviceList(t) {
      let e = await I.listDevices("", B._password),
        o = JSON.parse(e.json),
        s = o?.usb?.dfu ? o?.usb?.dfu : [],
        n = [],
        a = RegExp(/(?<=0x)\w\w\w\w/),
        r = 0,
        c = 0;
      return (
        s.forEach((l) => {
          let d = a.exec(l.vid)[0],
            m = a.exec(l.pid)[0],
            w = B.getDeviceTypeFromPID(m);
          (r =
            n.filter(
              (b) =>
                l.family === b.platform.toUpperCase() &&
                d === b.vid &&
                m === b.pid
            ).length + 1),
            m === this._vexAI3DCameraRAMPid
              ? n.push({
                  device: w.device,
                  pid: m,
                  vid: d,
                  bootMode: I.BootMode.ram,
                  platform: w.platform,
                  id: r,
                })
              : n.push({
                  device: w.device,
                  pid: m,
                  vid: d,
                  bootMode: I.BootMode.dfu,
                  platform: w.platform,
                  id: r,
                });
        }),
        t && (n = n.filter((l) => t === l.platform)),
        n
      );
    }
    getBootMode(t) {
      let e = JSON.parse(t),
        o,
        s = I.BootMode.unknown;
      if (e.v5) o = e.v5;
      else if (e.iq2) o = e.iq2;
      else if (e.exp) o = e.exp;
      else if (e?.unknown?.controller_boot) o = e.unknown;
      else return s;
      return (
        o?.brain?.bootloader
          ? o?.brain?.bootloader === I.BootMode.ram ||
            o?.brain?.bootloader === I.BootMode.rom
            ? (s = o?.brain?.bootloader)
            : (s = I.BootMode.unknown)
          : o?.brain
          ? (s = I.BootMode.app)
          : o?.controller
          ? (s = I.BootMode.app)
          : o?.controller_boot && (s = I.BootMode.rom),
        s
      );
    }
    startSearch() {
      if (
        (B._setStartTime(),
        B._logHandler("Starting VEX Device Search"),
        this._searchLoopID)
      ) {
        B._logHandler("Can't Start Loop because loop alread active");
        return;
      }
      this._searchLoopID = setInterval(() => {
        this._deviceDetectionLock ||
          this.deviceDetectionLoop().then(() => {
            this._deviceDetectionLock = !1;
          }),
          this._deviceDFUDetectionLock ||
            this.deviceDFULoop().then(() => {
              this._deviceDFUDetectionLock = !1;
            }),
          B._elapsedTime() > 1e4 && (B._startTime = new Date());
      }, 500);
    }
    resetSearch() {
      B._setStartTime(),
        B._logHandler("Reset VEX Device Search"),
        (this._activeDeviceList = []),
        this.stopSearch(),
        this.startSearch();
    }
    stopSearch() {
      B._logHandler("Stoping VEX Device Search"),
        clearInterval(this._searchLoopID),
        (this._searchLoopID = void 0);
    }
    on(t, e) {
      switch (t) {
        case "VEX_Device_Detected": {
          this._onDeviceDetect = e;
          break;
        }
        case "VEX_Device_Disconnected": {
          this._onDeviceDisconnect = e;
          break;
        }
        case "VEX_DFU_Device_Detected": {
          this._onDeviceDFUDetect = e;
          break;
        }
        case "VEX_DFU_Device_Disconnected": {
          this._onDeviceDFUDisconnect = e;
          break;
        }
        case "Log": {
          B._logCB = e;
          break;
        }
      }
    }
    async deviceDetectionLoop() {
      this._deviceDetectionLock = !0;
      let t = [],
        e = [],
        o = this._activeDeviceList,
        s = await B.getVEXDeviceList();
      (e = o.filter(
        (r) =>
          !s.some(
            (c) => c.communication === r.communication && c.user === r.user
          )
      )),
        e.forEach(async (r) => {
          B._logHandler(""),
            B._logHandler(`VEX ${r.platform} ${r.device} Disconnected `),
            B._logHandler("---------------------------------------------"),
            B._logHandler(`	-(User)           	 ${r.user}`),
            B._logHandler(`	-(Communication)  	 ${r.communication}`),
            i.DEBUG &&
              (B._logHandler(`	-(Robot Name) 	 ${r.robotName}`),
              B._logHandler(`	-(Team #)     	 ${r.teamNumber}`),
              B._logHandler(`	-(id)   	 ${r.id}`),
              B._logHandler(`	-(BootMode)       	 ${r.bootMode}`)),
            B._logHandler(""),
            (this._activeDeviceList = this._activeDeviceList.filter(
              (c) => c.communication !== r.communication
            )),
            this._disconnetHandler(r);
        }),
        (t = s.filter(
          (r) =>
            !o.some(
              (c) => c.communication === r.communication && c.user === r.user
            )
        ));
      let n = async (r) => {
          if (r.platform !== i.Platform.AI) {
            if (
              this.activeDeviceList.some(
                (m) => m.communication === r.communication
              )
            )
              return;
            let c = (await J.systemInfo(r.communication)).json,
              l = JSON.parse(c),
              d;
            if (l.v5) d = l.v5;
            else if (l.iq2) d = l.iq2;
            else if (l.exp) d = l.exp;
            else if (l.unknown) d = l.unknown;
            else return;
            (r.json = c),
              r.device === i.Device.Brain
                ? d.brain?.bootloader
                  ? d.brain.bootloader
                    ? ((r.robotName = `${d.brain.bootloader}`),
                      (r.id = ""),
                      (r.teamNumber = ""))
                    : !d.brain &&
                      d.controller &&
                      ((r.robotName = "Controller"),
                      (r.id = ""),
                      (r.teamNumber = ""))
                  : ((r.robotName = d.brain.name),
                    (r.id = d.brain.ssn),
                    (r.teamNumber = d.brain.team))
                : r.device === i.Device.Controller &&
                  (d.controller || d.controller_boot) &&
                  ((r.robotName = ""), (r.id = ""), (r.teamNumber = "")),
              (r.bootMode = this.getBootMode(c));
          } else
            r.platform === i.Platform.AI &&
              ((r.bootMode = I.BootMode.app), (r.json = "{}"));
          B._logHandler(""),
            B._logHandler(`VEX ${r.platform} ${r.device} Detected `),
            B._logHandler("---------------------------------------------"),
            B._logHandler(`	-(User)           	 ${r.user}`),
            B._logHandler(`	-(Communication)  	 ${r.communication}`),
            i.DEBUG &&
              (B._logHandler(`	-(Robot Name) 	 ${r.robotName}`),
              B._logHandler(`	-(Team #)     	 ${r.teamNumber}`),
              B._logHandler(`	-(id)         	 ${r.id}`),
              B._logHandler(`	-(BootMode)   	 ${r.bootMode}`)),
            B._logHandler(""),
            this._activeDeviceList.push(r),
            this._dectectHandler(r);
        },
        a = 0;
      for (
        t.forEach(async (r) => {
          await n(r), a++;
        });
        a !== t.length;

      )
        await i.Utils.asyncSleep(250);
    }
    async deviceDFULoop() {
      let t = [],
        e = [],
        o = this._activeDFUDeviceList,
        s = await B.getVEXDfuDeviceList();
      (e = o.filter(
        (r) =>
          !s.some((c) => r.id === r.id && r.vid === c.vid && r.pid === c.pid)
      )),
        this._dfuDisconnectCounter === this._maxDeviceDisconnects
          ? ((this._dfuDisconnectCounter = 0),
            e.forEach(async (r) => {
              B._logHandler(""),
                B._logHandler(
                  `VEX ${r.platform} ${r.device} (${r.bootMode}) Disconnected `
                ),
                B._logHandler("---------------------------------------------"),
                B._logHandler(`	-(VID)	 ${r.vid}`),
                B._logHandler(`	-(PID)	 ${r.pid}`),
                B._logHandler(`	-(Dummy ID)	 ${r.id}`),
                B._logHandler(""),
                (this._activeDFUDeviceList = this._activeDFUDeviceList.filter(
                  (c) => !(c.id === r.id && c.vid === r.vid && c.pid === r.pid)
                )),
                this._disconnetDFUHandler(r);
            }))
          : e.length
          ? this._dfuDisconnectCounter++
          : (this._dfuDisconnectCounter = 0),
        (t = s.filter(
          (r) =>
            !o.some((c) => c.id === r.id && c.vid === r.vid && c.pid === r.pid)
        ));
      let n = async (r) => {
          this._activeDFUDeviceList.some(
            (c) => c.id === r.id && c.vid === r.vid && c.pid === r.pid
          ) ||
            (B._logHandler(""),
            B._logHandler(
              `VEX ${r.platform} ${r.device} (${r.bootMode}) Detected `
            ),
            B._logHandler("---------------------------------------------"),
            B._logHandler(`	-(VID)	 ${r.vid}`),
            B._logHandler(`	-(PID)	 ${r.pid}`),
            B._logHandler(`	-(Dummy ID)	 ${r.id}`),
            B._logHandler(""),
            this._activeDFUDeviceList.push(r),
            this._dectectDFUHandler(r));
        },
        a = 0;
      for (
        t.forEach(async (r) => {
          await n(r), a++;
        });
        a !== t.length;

      )
        await i.Utils.asyncSleep(250);
    }
    static comparePortByPlatform(t, e, o) {
      switch (t) {
        case "Windows_NT":
          return e.serialNumber === o.serialNumber;
        case "Darwin":
          return e.locationId === o.locationId;
        case "Linux":
          let s = e.path.split("/").at(-1),
            n = o.path.split("/").at(-1),
            a = as
              .spawnSync(`find /sys/devices -name "${s}"`, {
                shell: !0,
              })
              .stdout.toString(),
            r = as
              .spawnSync(`find /sys/devices -name "${n}"`, {
                shell: !0,
              })
              .stdout.toString(),
            c = bo.dirname(bo.dirname(a)).split("."),
            l = bo.dirname(bo.dirname(r)).split(".");
          return (
            c.pop(), l.pop(), (a = c.join(".")), (r = l.join(".")), a === r
          );
        default:
          return !1;
      }
    }
    static getPortTypeByPlatform(t, e) {
      let o = "";
      switch (t) {
        case "Windows_NT":
          if (e.productId === this._vexAI3DCameraPid) {
            e.pnpId.includes(this._aicamcomsMI)
              ? (o = "Communication")
              : e.pnpId.includes(this._aicamuserMI) ||
                (e.vendorId === this._vexVid &&
                  e.productId === this._vexAI3DCameraPid)
              ? (o = "User")
              : (o = "Unknown");
            break;
          } else {
            e.pnpId.includes(this._comsMI) ||
            e.pnpId.includes(this._comsV5ControllerMI)
              ? (o = "Communication")
              : e.pnpId.includes(this._userMI)
              ? (o = "User")
              : (o = "Unknown");
            break;
          }
        case "Darwin":
          let s = e.path.slice(-1);
          if (e.productId === this._vexAI3DCameraPid) {
            s === this._aicamcomsModem
              ? (o = "Communication")
              : s === this._aicamuserModem
              ? (o = "User")
              : (o = "Unknown");
            break;
          } else {
            s === this._comsModem || s === this._comsV5ControllerModem
              ? (o = "Communication")
              : s === this._userModem
              ? (o = "User")
              : (o = "Unknown");
            break;
          }
        case "Linux":
          if (e.productId === this._vexAI3DCameraPid) {
            e.pnpId.includes(this._aicamcomsIF)
              ? (o = "Communication")
              : e.pnpId.includes(this._aicamuserIF)
              ? (o = "User")
              : (o = "Unknown");
            break;
          } else {
            e.pnpId.includes(this._comsIF) ||
            e.pnpId.includes(this._comsV5ControllerIF)
              ? (o = "Communication")
              : e.pnpId.includes(this._userIF)
              ? (o = "User")
              : (o = "Unknown");
            break;
          }
        default:
          o = "Unknown";
          break;
      }
      return o;
    }
    static filterbyType(t, e, o) {
      let s = o === "v5" || o === void 0,
        n = o === "exp" || o === void 0,
        a = o === "iq2" || o === void 0,
        r = cs.type();
      return t.filter(
        (l) =>
          l.vendorId === this._vexVid &&
          ((l.productId === this._vexAI3DCameraPid && (s || a)) ||
            (l.productId === this._v5BrainPid && s) ||
            (l.productId === this._v5ControllerPid && s) ||
            (l.productId === this._iq2BrainPid && a) ||
            (l.productId === this._iq2ControllerPid && a) ||
            (l.productId === this._expBrainPid && n) ||
            (l.productId === this._expControllerPid && n)) &&
          this.getPortTypeByPlatform(r, l) === e
      );
    }
    static getDeviceTypeFromPID(t) {
      switch (t) {
        case this._vexAI3DCameraPid:
          return {
            platform: i.Platform.AI,
            device: i.Device.Camera_3D,
          };
        case this._v5BrainPid:
          return {
            platform: i.Platform.V5,
            device: i.Device.Brain,
          };
        case this._v5ControllerPid:
          return {
            platform: i.Platform.V5,
            device: i.Device.Controller,
          };
        case this._expBrainPid:
          return {
            platform: i.Platform.EXP,
            device: i.Device.Brain,
          };
        case this._expControllerPid:
          return {
            platform: i.Platform.EXP,
            device: i.Device.Controller,
          };
        case this._iq2BrainPid:
          return {
            platform: i.Platform.IQ2,
            device: i.Device.Brain,
          };
        case this._iq2ControllerPid:
          return {
            platform: i.Platform.IQ2,
            device: i.Device.Controller,
          };
        case this._expBrainDFUPid:
          return {
            platform: i.Platform.EXP,
            device: i.Device.Brain,
          };
        case this._expControllerDFUPid:
          return {
            platform: i.Platform.EXP,
            device: i.Device.Controller,
          };
        case this._iq2BrainDFUPid:
          return {
            platform: i.Platform.IQ2,
            device: i.Device.Brain,
          };
        case this._iq2ControllerDFUPid:
          return {
            platform: i.Platform.IQ2,
            device: i.Device.Controller,
          };
        case this._vexAI3DCameraDFUPid:
          return {
            platform: i.Platform.AI,
            device: i.Device.Camera_3D,
          };
        case this._vexAI3DCameraRAMPid:
          return {
            platform: i.Platform.AI,
            device: i.Device.Camera_3D,
          };
        default:
          return {
            platform: i.Platform.Unknown,
            device: i.Device.Unknown,
          };
      }
    }
    static _sortListCB(t, e) {
      var o = `${t.platform} ${t.device}`.toUpperCase(),
        s = `${t.platform} ${t.device}`.toUpperCase();
      return o < s
        ? -1
        : o > s
        ? 1
        : t.communication < e.communication
        ? -1
        : t.communication > e.communication
        ? 1
        : 0;
    }
    static setPassword(t) {
      B._password = t;
    }
    static _setStartTime() {
      B._startTime = new Date();
    }
    static _elapsedTime() {
      return Number(new Date()) - Number(B._startTime);
    }
    static _logHandler(t, ...e) {
      let o = `${B._classType} ${t}`;
      e?.length
        ? (console.log(o, e), B._logCB && B._logCB(`${o} ${JSON.stringify(e)}`))
        : (console.log(o), B._logCB && B._logCB(o));
    }
    _dectectHandler(t) {
      this._onDeviceDetect && this._onDeviceDetect(t);
    }
    _disconnetHandler(t) {
      this._onDeviceDisconnect && this._onDeviceDisconnect(t);
    }
    _dectectDFUHandler(t) {
      this._onDeviceDFUDetect && this._onDeviceDFUDetect(t);
    }
    _disconnetDFUHandler(t) {
      this._onDeviceDFUDisconnect && this._onDeviceDFUDisconnect(t);
    }
    get activeDeviceList() {
      return this._activeDeviceList.filter((t) => t.platform !== i.Platform.AI);
    }
    get activeDFUDeviceList() {
      return this._activeDFUDeviceList.filter(
        (t) => t.platform !== i.Platform.AI
      );
    }
    get activeAIDeviceList() {
      return this._activeDeviceList.filter((t) => t.platform === i.Platform.AI);
    }
    get activeAIDFUDeviceList() {
      return this._activeDFUDeviceList.filter(
        (t) => t.platform === i.Platform.AI
      );
    }
    set selectedDevice(t) {
      this._selectedDevice = t;
    }
    get selectedDevice() {
      return this._selectedDevice;
    }
    set selectedAIDevice(t) {
      this._selectedAIDevice = t;
    }
    get selectedAIDevice() {
      return this._selectedAIDevice;
    }
  },
  ce = B;
(ce._classType = "Device Manager: "),
  (ce._vexVid = "2888"),
  (ce._nxpVid = "1FC9"),
  (ce._netChipTechVid = "0525"),
  (ce._expBrainPid = "0600"),
  (ce._expBrainDFUPid = "013D"),
  (ce._expControllerPid = "0610"),
  (ce._expControllerDFUPid = "061F"),
  (ce._iq2BrainPid = "0200"),
  (ce._iq2BrainDFUPid = "001F"),
  (ce._iq2ControllerPid = "0210"),
  (ce._iq2ControllerDFUPid = "021F"),
  (ce._v5BrainPid = "0501"),
  (ce._v5ControllerPid = "0503"),
  (ce._vexAI3DCameraPid = "0509"),
  (ce._vexAI3DCameraDFUPid = "0146"),
  (ce._vexAI3DCameraRAMPid = "A4A5"),
  (ce._comsMI = "MI_00"),
  (ce._userMI = "MI_02"),
  (ce._comsModem = "1"),
  (ce._userModem = "3"),
  (ce._comsIF = "if00"),
  (ce._userIF = "if02"),
  (ce._comsV5ControllerMI = "MI_01"),
  (ce._comsV5ControllerModem = "2"),
  (ce._comsV5ControllerIF = "if01"),
  (ce._aicamcomsMI = "MI_02"),
  (ce._aicamuserMI = "MI_00"),
  (ce._aicamcomsModem = "3"),
  (ce._aicamuserModem = "1"),
  (ce._aicamcomsIF = "if02"),
  (ce._aicamuserIF = "if00"),
  (ce._password = "");
var wo = L(require("child_process")),
  ao = L(require("path")),
  zs = L(require("os")),
  Ws = L(require("fs")),
  Gs = L(require("vscode"));
var Kt = class {
  constructor(t) {
    this._version = "1_1_0";
    this._installerName = "VEX Devices Driver Installer.exe";
    this._installSciptURI = Gs.Uri.joinPath(
      t.globalStorageUri,
      "drivers",
      this._installerName
    );
  }
  async listVEXDrivers() {
    let t = wo.spawnSync("driverquery /SI /NH /FO CSV", {
        shell: !0,
      }),
      e = [];
    return (
      new TextDecoder()
        .decode(t.stdout)
        .split(/[\r\n]+/)
        .forEach((n) => {
          let r = n.replace(/\"/gi, "").split(","),
            c = {
              name: r[0],
              driver: r[1],
              active: r[2],
              manufacterur: r[3],
            };
          e.push(c);
        }),
      console.log(e.filter((n) => n.manufacterur === "VEX Robotics Inc.")),
      e.filter((n) => n.manufacterur === "VEX Robotics Inc.")
    );
  }
  async run() {
    let t = (e, o) => {
      let s = "",
        n = "",
        a = "",
        r = {};
      r.PATH =
        ao.dirname(this._installSciptURI.fsPath) +
        ao.delimiter +
        process.env.PATH;
      let c = {
          shell: !0,
          env: r,
        },
        l = wo.spawn(`"${this._installerName}"`, [], c);
      console.log(l),
        l.stdout.on("data", function (d) {
          console.log(new TextDecoder().decode(d)),
            (a += new TextDecoder().decode(d));
        }),
        l.stderr.on("data", function (d) {
          console.log(new TextDecoder().decode(d)),
            (n += new TextDecoder().decode(d));
        }),
        l.on("exit", function (d) {
          console.log(d.toString(2)),
            e({
              stdout: a,
              stderr: n,
              exitCode: d,
            });
        });
    };
    return new Promise((e, o) => t(e, o));
  }
  async download() {
    return i.Extension.ResourceManager.downloadDriverInstaller(this._version);
  }
  get exist() {
    return (
      console.log(this._installSciptURI.fsPath),
      zs.type() === "Windows_NT"
        ? Ws.existsSync(this._installSciptURI.fsPath)
        : !0
    );
  }
  _executeCMD(t, e, o) {
    let s,
      n = (a, r) => {
        let c = "",
          l = "",
          d = "",
          m = {};
        m.PATH =
          ao.dirname(this._installSciptURI.fsPath) +
          ao.delimiter +
          process.env.PATH;
        let w = {
            shell: !0,
            env: m,
          },
          b = wo.spawn(`"${this._installerName}"`, [], w);
        console.log(b),
          b.stdout.on("data", function (C) {
            console.log(new TextDecoder().decode(C)),
              (d += new TextDecoder().decode(C));
          }),
          b.stderr.on("data", function (C) {
            console.log(new TextDecoder().decode(C)),
              (l += new TextDecoder().decode(C));
          }),
          b.on("exit", function (C) {
            console.log(C.toString(2)),
              a({
                stdout: d,
                stderr: l,
                exitCode: C,
              });
          });
      };
    return new Promise((a, r) => n(a, r));
  }
};
((a) => (
  (a.EXP_USER_PORT = "VEX EXP User Port"),
  (a.EXP_COM_PORT = "VEX EXP Communications Port"),
  (a.EXP_CONTROLLER_DFU = "VEX EXP cFirmware Upgrade"),
  (a.IQ2_USER_PORT = "VEX IQ User Port"),
  (a.IQ2_COM_PORT = "VEX IQ Communications Port"),
  (a.IQ2_CONTROLLER_DFU = "VEX IQ cFirmware Upgrade")
))(Kt || (Kt = {}));
var Mo = L(require("vscode")),
  qe = class {
    constructor(t, e, o) {
      (this._logHomeUri = Mo.Uri.joinPath(t.extensionUri, "_logs")),
        (this._outputBox = Mo.window.createOutputChannel(e, o));
    }
    _writeTextToLog(t) {}
    static _addLeadingZeros(t, e) {
      if (t < 0) {
        let o = String(t).slice(1);
        return "-" + o.padStart(e, "0");
      }
      return String(t).padStart(e, "0");
    }
    appendLine(t) {
      let e = `${qe.getTimeStamp()} ${t}`;
      this._outputBox.appendLine(e), this._writeTextToLog(e);
    }
    append(t) {
      let e = `${qe.getTimeStamp()} ${t}`;
      this._outputBox.append(e);
    }
    clear() {
      this._outputBox.clear();
    }
    hide() {
      this._outputBox.hide();
    }
    show() {
      this._outputBox.show();
    }
    static getTimeStamp() {
      let t = new Date(),
        e = qe._addLeadingZeros(t.getMonth() + 1, 2),
        o = qe._addLeadingZeros(t.getDate(), 2),
        s = qe._addLeadingZeros(t.getFullYear(), 4),
        n = qe._addLeadingZeros(t.getHours(), 2),
        a = qe._addLeadingZeros(t.getMinutes(), 2),
        r = qe._addLeadingZeros(t.getSeconds(), 2),
        c = qe._addLeadingZeros(t.getMilliseconds(), 3);
      return `[${e}/${o}/${s} ${n}:${a}:${r}:${c}]`;
    }
  };
var Ue = L(require("vscode")),
  Ze = L(require("fs")),
  ls = L(require("os")),
  Ao = require("util");
var It = class {
    constructor(t, e) {
      this._name = "";
      this._description = "";
      (this._projectUri = t),
        (this._settingsFileUri = Ue.Uri.joinPath(
          this._projectUri,
          ".vscode",
          It.vexProjectSettingsName
        )),
        (this._cppIntellisenseSettings = Ue.Uri.joinPath(
          this._projectUri,
          ".vscode",
          It.c_cpp_propertiesFileName
        )),
        (this._pythonIntellisenseSettings = Ue.Uri.joinPath(
          this._projectUri,
          ".vscode",
          It.python_propertiesFileName
        )),
        e && this.updateSettingsObj(e),
        this.writeProjectSettings(e);
    }
    updateSettingsObj(t) {
      (this._name = t.project.name ? t.project.name : ""),
        (this._description = t.project.description
          ? t.project.description
          : ""),
        (this._sdkVersion = t.project.sdkVersion ? t.project.sdkVersion : ""),
        (this._language = t.project.language
          ? t.project.language
          : i.Language.unknown),
        t.project.language === "cpp" &&
          ((this._includesUris = []),
          t?.project?.cpp?.includePath.forEach((e) => {
            this._includesUris.push(e);
          }));
    }
    readProjectSettings() {
      if (
        !Ze.existsSync(this._settingsFileUri.fsPath) ||
        !this._settingsFileUri.fsPath.includes(It.vexProjectSettingsName)
      )
        return;
      let t = Ze.readFileSync(this._settingsFileUri.fsPath);
      return JSON.parse(new Ao.TextDecoder().decode(t));
    }
    async writeProjectSettings(t) {
      this._lastProjectSettingsWrite = t;
      let e = Ue.Uri.joinPath(this._projectUri, ".vscode");
      !this._settingsFileUri.fsPath ||
        !t ||
        (Ze.existsSync(this._settingsFileUri.fsPath)
          ? (e = this._settingsFileUri)
          : (await Ue.workspace.fs.createDirectory(e),
            (e = Ue.Uri.joinPath(e, It.vexProjectSettingsName))),
        Ze.writeFileSync(e.fsPath, JSON.stringify(t, null, "	")),
        this.updateSettingsObj(t));
    }
    updateProjectSettings() {
      this.updateSettingsObj(this.readProjectSettings());
    }
    get lastProjectSettingsWrite() {
      return this._lastProjectSettingsWrite;
    }
    static readProjectSettings(t) {
      if (
        !Ze.existsSync(t.fsPath) ||
        !t.fsPath.includes(It.vexProjectSettingsName)
      )
        return;
      let e = Ze.readFileSync(t.fsPath);
      return JSON.parse(new Ao.TextDecoder().decode(e));
    }
    static async writeProjectSettings(t, e) {
      let o = Ue.Uri.joinPath(e, ".vscode"),
        s = Ue.Uri.joinPath(o, It.vexProjectSettingsName);
      !s.fsPath ||
        !t ||
        (Ze.existsSync(s.fsPath)
          ? (o = s)
          : (await Ue.workspace.fs.createDirectory(o),
            (o = Ue.Uri.joinPath(o, It.vexProjectSettingsName))),
        Ze.writeFileSync(o.fsPath, JSON.stringify(t, null, "	")));
    }
    async updateIntellesenseJSON(t) {
      let e = this.readProjectSettings(),
        o = Ue.Uri.joinPath(this._projectUri, ".vscode");
      if (e.project.language === "cpp") {
        let s = "";
        ls.type() === "Windows_NT" && (s = "clang"),
          ls.type() === "Darwin" && (s = "clang");
        let n = `${
            "${config:" + i.Extension.Settings.toolchainCPPPathID + "}"
          }`,
          a = Ue.Uri.file(""),
          r = Ue.Uri.joinPath(a, "clang", "bin", s),
          c = `${"${config:" + i.Extension.Settings.sdkCPPHomeID + "}"}`,
          l = Ue.Uri.joinPath(
            a,
            e.project.platform,
            this._sdkVersion,
            "vex" + e.project.platform.toLowerCase()
          );
        console.log(l);
        let d = {
          env: {
            vex_compilerPath: `${n}${r.fsPath}`,
            vex_sdkPath: `${c}${l.fsPath}`,
            vex_gcc:
              e.project.platform === "V5"
                ? "${vex_sdkPath}/gcc/include/c++/4.9.3"
                : "${vex_sdkPath}/gcc/include/c++/7.3.1",
            vex_sdkIncludes: [
              "${vex_sdkPath}/include/**",
              "${vex_sdkPath}/gcc/include/**",
              "${vex_sdkPath}/gcc/include/machine/**",
              "${vex_sdkPath}/gcc/include/newlib-nano/**",
              "${vex_sdkPath}/gcc/include/sys/**",
              "${vex_sdkPath}/clang/8.0.0/include/**",
              "${vex_gcc}/",
              "${workspaceFolder}/include/**",
              "${workspaceFolder}/src/**",
            ],
          },
          configurations: "",
          version: 4,
        };
        if (!this._cppIntellisenseSettings.fsPath || !d) return;
        Ze.existsSync(this._cppIntellisenseSettings.fsPath) ||
          (await Ue.workspace.fs.createDirectory(o),
          await Ue.workspace.fs.copy(t, this._cppIntellisenseSettings));
        let m = Ze.readFileSync(this._cppIntellisenseSettings.fsPath),
          w = JSON.parse(new Ao.TextDecoder().decode(m));
        if (d.env === w.env) return;
        (d.configurations = w.configurations),
          console.log("Settings URI:", this._cppIntellisenseSettings.fsPath),
          console.log("Settings JSON:", d),
          Ze.writeFileSync(
            this._cppIntellisenseSettings.fsPath,
            JSON.stringify(d, null, "	")
          );
      }
      if (e.project.language === "python") {
        Ze.existsSync(this._pythonIntellisenseSettings.fsPath) ||
          (await Ue.workspace.fs.createDirectory(o),
          await Ue.workspace.fs.copy(t, this._pythonIntellisenseSettings)),
          await i.Utils.asyncSleep(500);
        let s = Ue.workspace
          .getConfiguration()
          .get(i.Extension.Settings.sdkPythonHomeID);
        await Ue.workspace
          .getConfiguration()
          .update(
            i.Extension.Settings.pylanceStubPathID,
            `${s}\\${e.project.platform.toUpperCase()}\\${
              e.project.sdkVersion
            }\\vex${e.project.platform.toLowerCase()}\\stubs`,
            Ue.ConfigurationTarget.Workspace,
            !0
          ),
          await Ue.workspace
            .getConfiguration()
            .update(
              i.Extension.Settings.pylanceDiagnosticModePathID,
              "workspace",
              Ue.ConfigurationTarget.Workspace,
              !0
            ),
          await Ue.workspace
            .getConfiguration()
            .update(
              i.Extension.Settings.pylanceCheckingModeID,
              "basic",
              Ue.ConfigurationTarget.Workspace,
              !0
            );
      }
    }
    set name(t) {
      this._name = t.length <= 13 ? t : t.substring(0, 12);
    }
    get name() {
      return this._name;
    }
    get projectUri() {
      return this._projectUri;
    }
    get description() {
      return this._description;
    }
    get sdkVersion() {
      return this._sdkVersion;
    }
    get includeEnvUris() {
      return this._includesUris;
    }
    get language() {
      return this._language;
    }
    get settingsFileUri() {
      return this._settingsFileUri;
    }
  },
  ht = It;
(ht.vexProjectSettingsName = "vex_project_settings.json"),
  (ht.c_cpp_propertiesFileName = "c_cpp_properties.json"),
  (ht.python_propertiesFileName = "settings.json");
var $ = L(require("vscode")),
  xe = L(require("fs")),
  Fe = L(require("os")),
  ti = L(require("child_process")),
  Xe = require("util"),
  He = L(require("path"));
var te = L(require("vscode"));
var $i = (_, t, e, o, s, n) => `
    <vscode-data-grid-row class="row">
        <vscode-data-grid-cell grid-column="1">
            <section class="component-row">
                <section class="component-container">
                    <img src="${t}" alt="${n} Project Icon" >
                </section>
                <section class="component-container">
                    <h3 id="project-title-${_}" class="zeroMargin project-title">${e}</h3>
                    <p  id="project-description-${_}" class="p-description project-description">${o}</p>
                    <section id="project-tags-${_}" class="label-row">
                        ${s}
                    </section>
                </section>

            </section>
        </vscode-data-grid-cell>
    </vscode-data-grid-row>
`,
  Ni = (_) => `<vscode-tag>${_}</vscode-tag>`,
  Ft = class {
    constructor(t) {
      console.log(t),
        (this._id = t ? t.id : ""),
        (this._iconUri = t ? t.iconUri : void 0),
        (this._projectName = t ? t.projectName : ""),
        (this._description = t ? t.description : ""),
        (this._tags = t ? t.tags : []),
        (this._platform = t ? t.platform : ""),
        console.log(this);
    }
    set iconUri(t) {
      this._iconUri = t;
    }
    set projectName(t) {
      this._projectName = t;
    }
    set description(t) {
      this._description = t;
    }
    set tags(t) {
      this._tags = t;
    }
    get html() {
      return $i(
        this._id,
        this._iconUri,
        this._projectName,
        this._description,
        this._getTagHtml(),
        this._platform
      );
    }
    _getTagHtml() {
      let t = "";
      return (
        this._tags.length &&
          this._tags.forEach((e) => {
            t += Ni(e);
          }),
        t
      );
    }
    static html(t) {
      let e = "";
      return (
        t &&
          ((e +=
            '<vscode-data-grid id="ListContainer" generate-header="none" aria-label="Basic" class="project-list">'),
          t.forEach((o) => {
            e += o.html;
          }),
          (e += "</vscode-data-grid>")),
        e
      );
    }
    static getObjsFromOptionList(t) {
      if (!t) return [];
      let e = [];
      return (
        t.forEach((o) => {
          e.push(new Ft(o)), console.log(e);
        }),
        e
      );
    }
  };
var Mi = (_, t, e, o) => `
    <vscode-data-grid-row class="row platform-row">
        <vscode-data-grid-cell grid-column="1" style="height:auto!important; padding-top:10%!important; padding-bottom:10%!important;">
            <div class="platform-container">
                <div class="platform-image-container">
                    <img class="platform-img" src="${t}" alt="${o} Project Icon" >
                </div>
                <div class="platform-title-container">
                    <h2 id="project-title-${_}" class="platform-title">${e}</h2>
                </div>
            </div>

        </vscode-data-grid-cell>
    </vscode-data-grid-row>
`;
var Qt = class {
  constructor(t) {
    console.log(t),
      (this._id = t ? t.id : ""),
      (this._iconUri = t ? t.iconUri : void 0),
      (this._projectName = t ? t.platformName : ""),
      (this._platform = t ? t.platform : ""),
      console.log(this);
  }
  set iconUri(t) {
    this._iconUri = t;
  }
  set projectName(t) {
    this._projectName = t;
  }
  get html() {
    return Mi(this._id, this._iconUri, this._projectName, this._platform);
  }
  static html(t) {
    let e = "";
    return (
      t &&
        ((e +=
          '<vscode-data-grid id="ListContainer" generate-header="none" aria-label="Basic" class="platform-list">'),
        t.forEach((o) => {
          e += o.html;
        }),
        (e += "</vscode-data-grid>")),
      e
    );
  }
  static getObjsFromOptionList(t) {
    if (!t) return [];
    let e = [];
    return (
      t.forEach((o) => {
        e.push(new Qt(o)), console.log(e);
      }),
      e
    );
  }
};
var Ai = (_, t, e) => `
    <vscode-data-grid-row class="row platform-row">
    <vscode-data-grid-cell grid-column="1" style="height:auto!important; padding-top:10%!important; padding-bottom:10%!important;">
        <div class="platform-container">
            <div class="platform-image-container">
            <img class="language-img" src="${t}" alt="${e} Language Icon" >
            </div>
            <div class="platform-title-container">
            <h2 id="language-title-${_}" class="language-title">${e}</h2>
            </div>
        </div>

    </vscode-data-grid-cell>
</vscode-data-grid-row>
`,
  Yt = class {
    constructor(t) {
      console.log(t),
        (this._id = t ? t.id : ""),
        (this._iconUri = t ? t.iconUri : void 0),
        (this._languageName = t ? t.languageTitle : ""),
        console.log(this);
    }
    set iconUri(t) {
      this._iconUri = t;
    }
    set projectName(t) {
      this._languageName = t;
    }
    get html() {
      return Ai(this._id, this._iconUri, this._languageName);
    }
    static html(t) {
      let e = "";
      return (
        t &&
          ((e +=
            '<vscode-data-grid id="ListContainer" generate-header="none" aria-label="Basic" class="platform-list">'),
          t.forEach((o) => {
            e += o.html;
          }),
          (e += "</vscode-data-grid>")),
        e
      );
    }
    static getObjsFromOptionList(t) {
      if (!t) return [];
      let e = [];
      return (
        t.forEach((o) => {
          e.push(new Yt(o)), console.log(e);
        }),
        e
      );
    }
  };
var j = L(require("vscode")),
  Li = [
    {
      projectName: "V5 Empty Template Project",
      description: "This is a V5 python template project",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Empty"],
      zipName: "py_v5_vsc_empty.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "V5 Clawbot Project",
      description: "This is an V5 python Clawbot project",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_v5_vsc_clawbot.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Clawbot Controller with Events",
      description:
        "This example will use Controller button events to control the V5 Clawbot arm and claw",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_v5_vsc_clawbot_controller_tank.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Drive to Location (Known Starting Position)",
      description:
        "This example will show how to use a GPS Sensor to navigate a V5 Moby Hero Bot to the center of a field by driving along the X-axis then the Y-axis",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "py_v5_vsc_drive_to_location_gps.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Drivetrain Sensing",
      description:
        "This example will show all of the available commands for using the Drivetrain",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "py_v5_vsc_drivetrain_sensing.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Limit / Bumper Sensing",
      description:
        "This example will show all of the available commands for using the Limit and Bumper Sensors",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "py_v5_vsc_limit_bumper_sensing.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Right Arcade Control",
      description:
        "This example will use the right X/Y Controller axis to control the Clawbot.",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_v5_vsc_right_arcade_control.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Split Arcade Control",
      description:
        "This example will use the left Y and right X Controller axis to control the Clawbot.",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: [, "Clawbot"],
      zipName: "py_v5_vsc_split_arcade_control.zip",
      platform: "V5",
      language: "python",
    },
    {
      projectName: "Using Threads",
      description:
        "This example will show how to run multiple threads (tasks) in a project at the same time",
      iconUri: j.Uri.file("v5python.png"),
      id: "",
      tags: ["Control"],
      zipName: "py_v5_vsc_using_threads.zip",
      platform: "V5",
      language: "python",
    },
  ],
  Oi = [
    {
      projectName: "EXP Empty Template Project",
      description: "This is a EXP python template project",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Empty"],
      zipName: "py_exp_vsc_empty.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "EXP Clawbot Project",
      description: "This is an EXP python Clawbot project",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_exp_vsc_clawbot.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Clawbot Controller with Events",
      description:
        "The Left up/down Controller Axis (A) will control the speed of the left motor. The Right up/down Controller Axis (D) will control the  speed of the right motor. The Left up/down Controller Buttons will control the Arm. The Right up/down Controller Buttons will control the Claw",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_exp_vsc_clawbot_controller_tank.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Drivetrain Sensing",
      description:
        "This example will print Drivetrain-related information to the EXP Brain's Screen",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "py_exp_vsc_drivetrain_sensing.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Limit / Bumper Sensing",
      description:
        "This example will show all of the available commands for using the Limit and Bumper Sensors",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "py_exp_vsc_limit_bumper_sensing.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Right Arcade",
      description:
        "The Right up/down Controller Axis (2) will drive the robot forward and backwards. The Right left/right Controller Axis (1) will turn the robot left and right. The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: [, "Clawbot"],
      zipName: "py_exp_vsc_right_arcade_control.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Split Arcade",
      description:
        "The Left up/down Controller Axis (3) will drive the robot forward and backwards. The Right left/right Controller Axis (1) will turn the robot left and right. The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_exp_vsc_split_arcade_control.zip",
      platform: "EXP",
      language: "python",
    },
    {
      projectName: "Using Threads",
      description:
        "This example will show how to run multiple threads (tasks) in a project at the same time",
      iconUri: j.Uri.file("exppython.png"),
      id: "",
      tags: ["Control"],
      zipName: "py_exp_vsc_using_threads.zip",
      platform: "EXP",
      language: "python",
    },
  ],
  Bi = [
    {
      projectName: "IQ2 Empty Template Project",
      description: "This is a IQ2 python template project",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Empty"],
      zipName: "py_iq2_vsc_empty.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "IQ2 Clawbot Project",
      description: "This is an IQ2 python Clawbot project",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_iq2_vsc_clawbot.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "Base Robot With Sensors",
      description: "Base IQ Gen 2 robot with controls and with sensors",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Basebot"],
      zipName: "py_iq2_vsc_basebot_with_sensors.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "Controlling Fling",
      description:
        "This program shows how to control Fling's motors with the controller events and the drivetrain with the configured controller. The Left up/down controller buttons will control the Intake Motor. The Right up/down controller buttons will control the Catapult Motor. The Joysticks are configured for Tank control",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Herobot"],
      zipName: "py_iq2_vsc_herobot_fling_with_controller.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "PLTW Template",
      description: "An empty project for the Project Lead The Way chassis",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["PLTW"],
      zipName: "py_iq2_vsc_pltw_chassis.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "Split Arcade",
      description:
        "The Left up/down Controller Axis (A) will drive the robot forward and backwards. The Right left/right Controller Axis (C) will turn the robot left and right. The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "py_iq2_vsc_split_arcade.zip",
      platform: "IQ2",
      language: "python",
    },
    {
      projectName: "Using Threads",
      description:
        "This example will show how to run multiple threads (tasks) in a project at the same time",
      iconUri: j.Uri.file("iqpython.png"),
      id: "",
      tags: ["Control"],
      zipName: "py_iq2_vsc_thread_example.zip",
      platform: "IQ2",
      language: "python",
    },
  ],
  Fi = [
    {
      projectName: "V5 Empty Template Project",
      description: "This is a template for an empty V5 project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Empty"],
      zipName: "cpp_v5_vsc_empty.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "V5 Competition Template Project",
      description: "This is a V5 competition template project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Competition"],
      zipName: "cpp_v5_vsc_competition_template.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Controller with Events",
      description:
        "This example will use Controller button events to control the V5 Clawbot arm and claw",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_v5_vsc_clawbot_controller_tank.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Template (Drivetrain 2-motor)",
      description: "Clawbot Template (Drivetrain 2-motor)",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "Claw_Drive_Temp.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Template (Drivetrain 4-motor)",
      description: "Blank Pre-Configured V5 Clawbot 4-motor Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "Claw_4drive_gyro_temp.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Template (2-motor Drivetrain, No Gyro)",
      description: "Blank Pre-Configured V5 Clawbot 2-motor Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "Drive_Temp_Nogyro.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Template (4-motor Drivetrain, No Gyro)",
      description: "Blank Pre-Configured V5 Clawbot 4-motor Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "Claw_4drive_Nogyro_temp.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Template (Motors)",
      description: "Blank Pre-Configured V5 Clawbot Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "Claw_Motor_Temp.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Competition Template",
      description: "Competition template with a Clawbot configured",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Competition", "Clawbot"],
      zipName: "Clawbot_Competition.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Competition Template",
      description: "Competition template with no devices configured",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Competition"],
      zipName: "Competition_Template.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "SDV(Drivetrain 2 - motor)",
      description: "Blank Pre - Configured SDV Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["SDV "],
      zipName: "SDV_Drivetrain.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "SDV(Motors)",
      description: "Blank Pre - Configured SDV Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["SDV"],
      zipName: "SDV_Motors.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Speedbot(Drivetrain 2 - motor, No Gyro)",
      description:
        "Blank Pre - Configured V5 Speedbot 2 - motor Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Speedbot"],
      zipName: "Speedbot_DT_NoGyro.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Speedbot(Drivetrain 4 - motor, No Gyro)",
      description:
        "Blank Pre - Configured V5 Speedbot 4 - motor Drivetrain Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Speedbot"],
      zipName: "Speed_bot_fourDT.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Speedbot(Motors)",
      description: "Blank Pre - Configured V5 Speedbot Project",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Speedbot"],
      zipName: "Speedbot_Motors.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Claw and Arm ",
      description: "Use the claw and arm to transport an object",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Claw"],
      zipName: "Claw_And_Arm.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Using The Arm(degrees)",
      description: "Raise and lower the arm to specific positions",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Claw"],
      zipName: "Using_The_Arm.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Using The Claw(degrees)",
      description: "Open and close the claw on your V5 robot",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Claw"],
      zipName: "Using_The_Claw.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Adjusting Speed",
      description: "Change the speed of a drivetrain 's drive and turn actions",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Adjusting_Speed.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drivetrain with Variables",
      description: "Change the drive distance with variables",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Drivetrain_With_Vars.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drivetrain Sensing",
      description:
        "This example will show all of the available commands for using the Drivetrain",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "cpp_v5_vsc_drivetrain_sensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Moving Backwards (inches)",
      description: "Drives the robot in reverse for 6 inches",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Moving_Backwards_In.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Moving Backwards (mm)",
      description: "Drives the robot in reverse for 150 millimeters",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Moving_Backwards_Mm.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Moving Forward (inches)",
      description: "Drives the robot forward for 6 inches",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Moving_Forward_In.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Moving Forward (mm)",
      description: "Drives the robot forward for 150 millimeters",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Moving_Forward_Mm.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Turning Left (degrees)",
      description: "Turns the robot left 90 degrees",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["V5", "Drivetrain"],
      zipName: "Turn_Left_Degrees.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Turning Right (degrees)",
      description: "Turns the robot right 90 degrees",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Drivetrain"],
      zipName: "Turn_Right_Degrees.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Electromagnet Actions",
      description: "Use the electromagnet to pick up and drop magnetic objects",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Magnet"],
      zipName: "Electromagnet_Actions.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Electromagnet Actions",
      description: "Use the electromagnet to pick up and drop magnetic objects",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Magnet"],
      zipName: "Electromagnet_Actions.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Display Position",
      description:
        "Displays the current position of the arm on the brain's screen",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmDisplayPosition.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Install",
      description: "Setup the potentiometersfor your V5 Workcell arm",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmInstall.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Jogging",
      description:
        "Control the Workcell Arm by pressing buttons on the screen of the V5 Brain",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmJogging.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Manual Movement",
      description:
        "Displays the current position of the arm on the V5 Brain 's screen and move the arm around manually",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmManualMovement.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Mastering",
      description:
        "Helps you to find the mastering values for your Workcell Arm",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmMastering.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm UI Panel",
      description:
        "Configure the Workcell Arm and display a basic UI on the V5 Brain's screen that you can configure",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmUIPanel.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Workcell - No Sensors",
      description: "Get started with the V5 Workcell without sensors",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmWorkcellNoSensors.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Arm Workcell - With Sensors",
      description: "Get started with the V5 Workcell with sensors",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Workcell"],
      zipName: "ArmWorkcellSensors.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drawing Shapes",
      description: "Learn to draw shapes and lines on the V5 Brain 's Screen.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Looks"],
      zipName: "Drawing_Shapes.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Printing Text",
      description: "Print text to the V5 Brain's Screen",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Looks"],
      zipName: "Printing_Text.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Comparing Values ",
      description: "Print text based on the value of a number",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Comparing_Values.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Creating a Start Button",
      description: "Press the Brain 's Screen to start your program",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Create_Start_Button.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Floor Sweeper",
      description: "Use random numbers to calculate turns",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Floor_Sweeper.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Functions (Returns)",
      description: "Use a function to add ten to an integer",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Functions_Returns.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Functions (No Returns)",
      description: "Use a function to print messages on empty rows",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Functions_NoReturn.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Making Decisions",
      description: "Use the range finder to make a decision",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Making_Decisions.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Multitasking (Tasks)",
      description: "Use tasks to run multiple functions at the same time.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Multitasking_Tasks.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Multithreading (Threads)",
      description: "Use threads to run multiple functions at the same time.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Multithreading_Threads.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Repeating Actions",
      description: "Use a loop to repeat robot movements",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Repeating_Actions.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Repeating Actions (Clawbot)",
      description: "Use a loop to repeat robot movements",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Repeating_ActionClaw.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Repeating Actions (No Gyro)",
      description: "Use a loop to repeat robot movements",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "Repeating_ActionNoGy.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Accurate Turns",
      description: "Use the Gyro to turn 90 degrees",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Accurate_turns.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Accurate Turns (Inertial Sensor)",
      description: "Use the Inertial Sensor to turn 90 degrees",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Accurate_turns_inert.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Clawbot Control",
      description: "Use events to drive the clawbot",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing", "Clawbot"],
      zipName: "Clawbot_Control.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Controller Buttons",
      description: "Using the V5 Controller Buttons",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Controller_Buttons.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detect Collisions",
      description: "Use the accelerometer to detect collisions",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Detect_Collisions.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detecting Distances",
      description: "Use the Range Finder to detect distance",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Detecting_Distances.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detecting Light",
      description: "Use the Light Sensor to detect the lighting of the room",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Detecting_Light.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detecting Objects(Vision)",
      description: "Use the Vision Sensor to detect three colors",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Detecting_Objects.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detecting Walls(Bumper)",
      description: "Stops the robot when the Bumper is pressed",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Detecting_Walls.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Detecting Walls(Bumper on 3 - Wire Expander)",
      description: "Stops the robot when the Bumper is pressed",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "3 - wire_expander.zip ",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Digital In Sensing",
      description:
        "Use a Digital In device to read input signals from another device",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "DigitalInSensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Digital Out Sensing",
      description: "Control another device using the Digital Out device",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "DigitalOutSensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drive to Location(Known Starting Position)",
      description:
        "Use a GPS Sensor to drive to a field 's center along the X-axis, then the Y-axis, from a known starting position",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "DriveLocationKnown.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drive to Location (Unknown Starting Position)",
      description:
        "Use a GPS Sensor to drive to a specified position from a random starting position",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "DriveLocationUnknown.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drive to Location (Using Tangents)",
      description:
        "Use a GPS Sensor to drive directly to a field's center from a random starting position",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing "],
      zipName: "DriveLocationTangent.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Drive to Location(Known Starting Position)",
      description:
        "This example will show how to use a GPS Sensor to navigate a V5 Moby Hero Bot to the center of a field by driving along the X - axis then the Y - axis ",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "cpp_v5_vsc_drive_to_location_gps.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Distance Sensing",
      description:
        "Use the Distance Sensor to get distance and size information of an object",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Distance_Sensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Inertial Printing Demo",
      description: "Prints values of the Inertial Sensor",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Inertial_printing_demo.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Left Arcade ",
      description: "Control the V5 Clawbot with the left joystick",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Left_Arcade.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Limiting Movement",
      description: "Use a limitswitch to stop arm movement",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Limiting_Movement.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Limit / Bumper Sensing",
      description:
        "This example will show all of the available commands for using the Limit and Bumper Sensors",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "cpp_v5_vsc_limit_bumper_sensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Line Tracking",
      description: "Move a robot a long a line by tracking it",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Line_Tracking.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Optical Sensing",
      description:
        "Use an Optical Sensor to get hue and brightness values of an object ",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Optical_Sensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Positioning Servos",
      description: "This program will spin the servo to different positions",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Positioning_Servos.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Reading Angles",
      description: "Print the potentiometer values to the V5 Brain 's Screen",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Reading_Angles.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Right Arcade",
      description: "Print the potentiometer values to the V5 Brain's Screen",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Reading_Angles.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Right Arcade Control",
      description:
        "This example will use the right X / Y Controller axis to control the Clawbot.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "cpp_v5_vsc_right_arcade_control.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Rotation Sensing",
      description:
        "Use a Rotation Sensor to get angular and positional data of an axle",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Rotation_Sensing.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Split Arcade",
      description: "Control the V5 Clawbot with both joysticks.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Split_Arcade.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Tank Drive",
      description: "Control the V5 Clawbot with both joysticks.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Tank_Drive.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Using 393 s",
      description: "Using 393 s with your V5 robot",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Using_393s.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Using LEDs",
      description: "Turn LEDs on and off",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Using_LEDS.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "Using Quad Encoders",
      description: "Use Quad Encoders to track the rotation of a shaft",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "Using_Quad_Encoders.zip",
      platform: "V5",
      language: "cpp",
    },
    {
      projectName: "2 D Arrays",
      description: "Use nested for loops to print values of a 2 D Array.",
      iconUri: j.Uri.file("v5cpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "2 D_Arrays.zip",
      platform: "V5",
      language: "cpp",
    },
  ],
  Xi = [
    {
      projectName: "EXP Empty Template Project",
      description: "This is a templatefor a simple EXP project",
      iconUri: j.Uri.file("expcpp.png"),
      id: "",
      tags: ["Empty"],
      zipName: "cpp_exp_vsc_empty.zip",
      platform: "EXP",
      language: "cpp",
    },
    {
      projectName: "ClawBot Controller With Events",
      description:
        "The Left up / down Controller Axis(3) will control the speed of the left motor.The Right up / down Controller Axis(2) will control the speed of the right motor.The Left up / down Controller Buttons will control the Arm.The Right up / down Controller Buttons will control the Claw.",
      iconUri: j.Uri.file("expcpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_exp_vsc_clawbot_controller_tank.zip",
      platform: "EXP",
      language: "cpp",
    },
    {
      projectName: "Drivetrain Sensing",
      description:
        "This example will print Drivetrain - related information to the EXP Brain 's Screen",
      iconUri: j.Uri.file("expcpp.png"),
      id: "",
      tags: ["Sensing"],
      zipName: "cpp_exp_vsc_drivetrain_sensing.zip",
      platform: "EXP",
      language: "cpp",
    },
    {
      projectName: "Right Arcade",
      description:
        "The Right up/down Controller Axis (2) will drive the robot forward and backwards. The Right left/right Controller Axis (1) will turn the robot left and right. The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("expcpp.png "),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_exp_vsc_right_arcade_control.zip",
      platform: "EXP",
      language: "cpp",
    },
    {
      projectName: "Split Arcade ",
      description:
        "The Left up / down Controller Axis(3) will drive the robot forward and backwards.The Right left / right Controller Axis(1) will turn the robot left and right.The deadband variable prevents drift when the Controller 's joystick is released.",
      iconUri: j.Uri.file("expcpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_exp_vsc_split_arcade_control.zip",
      platform: "EXP",
      language: "cpp",
    },
    {
      projectName: "Using Threads",
      description:
        "This example will show how to run multiple threads (tasks) in a project at the same time",
      iconUri: j.Uri.file("expcpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "cpp_exp_vsc_using_threads.zip",
      platform: "EXP",
      language: "cpp",
    },
  ],
  Hi = [
    {
      projectName: "IQ 2nd Generation Empty Project",
      description: "This is a template for a simple IQ2 project",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Empty"],
      zipName: "cpp_iq2_vsc_empty.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "IQ2 Clawbot Project",
      description: "This is an IQ2 python Clawbot project",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_iq2_vsc_clawbot_controller.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "Base Robot With Sensors",
      description: "Base IQ Gen 2 robot with controls and with sensors",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Basebot"],
      zipName: "cpp_iq2_vsc_basebot_with_sensors.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "Controlling Fling",
      description:
        "This program shows how to control Fling's motors with the controller events and the drivetrain with the configured controller.The Left up / down controller buttons will control the Intake Motor.The Right up / down controller buttons will control the Catapult Motor.The Joysticks are configured for Tank control",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Herobot"],
      zipName: "cpp_iq2_vsc_herobot_fling_controller.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "PLTW Template",
      description: "An empty projectfor the Project Lead The Way chassis",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["PLTW"],
      zipName: "cpp_iq2_vsc_pltw_chassis.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "Split Arcade",
      description:
        "The Left up / down Controller Axis(A) will drive the robot forward and backwards.The Right left / right Controller Axis(C) will turn the robot left andright.The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Clawbot"],
      zipName: "cpp_iq2_vsc_split_arcade.zip",
      platform: "IQ2",
      language: "cpp",
    },
    {
      projectName: "Split Arcade",
      description:
        "The Left up/down Controller Axis (A) will drive the robot forward and backwards. The Right left/right Controller Axis (C) will turn the robot left and right. The deadband variable prevents drift when the Controller's joystick is released.",
      iconUri: j.Uri.file("iqcpp.png"),
      id: "",
      tags: ["Control"],
      zipName: "cpp_iq2_vsc_thread_example.zip",
      platform: "IQ2",
      language: "cpp",
    },
  ],
  zi = [],
  Co = zi.concat(Fi, Xi, Hi, Li, Bi, Oi);
var qs = L(require("os")),
  ds = require("fs"),
  Wi = require("path"),
  ae = class {
    static async Show(t) {
      if ((console.log("resolve Webview"), ae._isRunning))
        return (
          this._panel.reveal(this._panel.viewColumn),
          {
            event: "isRunning ",
            projectPath: "",
            projectIndex: -1,
            vexSettings: {
              extension: {
                version: "",
                json: 1,
              },
              project: {
                sdkVersion: "",
                creationDate: "",
                description: "",
                language: void 0,
                name: "",
                platform: void 0,
                slot: 1,
              },
            },
            zipName: "",
          }
        );
      (ae._extensionUri = t),
        (ae._isRunning = !0),
        (ae._projectOptionsList = Co);
      let e = te.window.activeTextEditor
          ? te.window.activeTextEditor.viewColumn
          : void 0,
        o = te.window.createWebviewPanel(
          ae.viewType,
          "Create New Project ",
          e || te.ViewColumn.One
        );
      return console.log("resolve Webview"), await ae.resolveWebviewView(o);
    }
    static async resolveWebviewView(t) {
      console.log("resolve Webview"), (this._panel = t);
      let e = !1;
      console.log("resolve Webview");
      let o = {
        event: "create",
        projectPath: "",
        projectIndex: -1,
        vexSettings: {
          extension: {
            version: "",
            json: 1,
          },
          project: {
            sdkVersion: "",
            creationDate: "",
            description: "",
            language: void 0,
            name: "",
            platform: void 0,
            slot: 1,
          },
        },
        zipName: "",
      };
      for (
        t.webview.options = {
          enableScripts: !0,
          localResourceRoots: [
            te.Uri.joinPath(ae._extensionUri, "resources", "icons"),
            te.Uri.joinPath(ae._extensionUri, "resources", "webviews"),
            te.Uri.joinPath(ae._extensionUri, "dist", "webviews", "views"),
            te.Uri.joinPath(
              ae._extensionUri,
              "node_modules",
              "@vscode",
              "webview - ui - toolkit",
              "dist"
            ),
            te.Uri.joinPath(
              ae._extensionUri,
              "node_modules",
              "@vscode",
              "codicons",
              "dist"
            ),
            te.Uri.joinPath(ae._extensionUri, "resources", "webviews", "libs"),
          ],
        },
          t.webview.html = ae._getHtmlForWebview(t.webview),
          t.webview.onDidReceiveMessage((s) => {
            if ((console.log("Provider Recieved", s), !!s))
              switch (s.type) {
                case "cancelBtn": {
                  (ae._isRunning = !1),
                    (o.event = "cancel"),
                    (o.projectIndex = -1),
                    (o.zipName = ""),
                    (o.vexSettings = void 0),
                    t.dispose();
                  break;
                }
                case "browseBtn": {
                  console.log("browse btn clicked");
                  let a = {
                    defaultUri: te.Uri.file(
                      te.workspace
                        .getConfiguration()
                        .get(
                          i.Extension.Settings.projectHomeID,
                          te.ConfigurationTarget.Global
                        )
                        .toString()
                    ),
                    canSelectFolders: !0,
                    canSelectFiles: !1,
                    canSelectMany: !1,
                  };
                  te.window.showOpenDialog(a).then((r) => {
                    if (!r) {
                      console.log("undefined file uri");
                      return;
                    }

                    console.log(r[0]),
                      this._panel.webview.postMessage({
                        type: s.type,
                        path: r[0].fsPath,
                      });
                  });

                  break;
                }
                case "updateAndCheckFolderListAtPathFinal":
                case "updateAndCheckFolderListAtPath":
                case "updateFolderListAtPath": {
                  if (!(0, ds.existsSync)(s.path)) {
                    this._panel.webview.postMessage({
                      type: s.type,
                      paths: [],
                    });
                    break;
                  }
                  console.log("Updated Folder List", s),
                    te.workspace.fs
                      .readDirectory(te.Uri.file(s.path))
                      .then((n) => {
                        let a = [];
                        console.log("Folder List", n),
                          n.forEach((r) => {
                            r[1] === te.FileType.Directory && a.push(r[0]);
                          }),
                          console.log("Folder String List", a),
                          this._panel.webview.postMessage({
                            type: s.type,
                            paths: a,
                          }),
                          console.log("Updated Folder List Finished", s);
                      });

                  break;
                }
                case "createProject": {
                  let n =
                      ae._languageOptionsList[
                        s.simple_project_settings.language_index
                      ].language,
                    a =
                      ae._platformOptionsList[
                        s.simple_project_settings.platform_index
                      ].platform,
                    r = ae._projectOptionsList.filter((d) =>
                      d.language === n && d.platform === a ? 1 : 0
                    ),
                    c,
                    l;
                  n === "cpp"
                    ? (c = {
                        extension: { version: i.Extension.version(), json: 1 },
                        project: {
                          name: s.simple_project_settings.name,
                          description: s.simple_project_settings.description,
                          creationDate: i.Utils.getDateString(),
                          platform:
                            r[s.simple_project_settings.project_index].platform,
                          language:
                            r[s.simple_project_settings.project_index].language,
                          slot: 1,
                          sdkVersion: "",
                          cpp: { includePath: [] },
                        },
                      })
                    : n === "python" &&
                      (c = {
                        extension: { version: i.Extension.version(), json: 1 },
                        project: {
                          name: s.simple_project_settings.name,
                          description: s.simple_project_settings.description,
                          creationDate: i.Utils.getDateString(),
                          platform:
                            r[s.simple_project_settings.project_index].platform,
                          language:
                            r[s.simple_project_settings.project_index].language,
                          slot: 1,
                          sdkVersion: "",
                          python: { main: "src / main.py" },
                        },
                      }),
                    (o.event = "create"),
                    (o.projectPath = te.Uri.file(
                      s.simple_project_settings.projectPath
                    ).fsPath),
                    (o.projectIndex = s.simple_project_settings.project_index),
                    (o.zipName =
                      r[s.simple_project_settings.project_index].zipName),
                    (o.vexSettings = c),
                    (ae._isRunning = !1),
                    t.dispose();
                  break;
                }
                case "sdkOptions": {
                  let n = ae._platformOptionsList[s.platform_index].platform,
                    a = ae._languageOptionsList[s.language_index].language,
                    r,
                    c;
                  switch (a) {
                    case "python":
                      c = te.Uri.file(
                        te.workspace
                          .getConfiguration()
                          .get(
                            i.Extension.Settings.sdkPythonHomeID,
                            te.ConfigurationTarget.Global
                          )
                          .toString()
                      );
                      break;
                    case "cpp":
                      c = te.Uri.file(
                        te.workspace
                          .getConfiguration()
                          .get(
                            i.Extension.Settings.sdkCPPHomeID,
                            te.ConfigurationTarget.Global
                          )
                          .toString()
                      );
                      break;
                  }
                  console.log("Language", a),
                    (r = async () =>
                      i.Extension.ResourceManager.getSDKVersion(n, a, c)),
                    console.log("sdkOptions", s),
                    r().then((l) => {
                      let d = "",
                        m = [],
                        w = JSON.parse(l.json);
                      w.online.catalog.forEach((b) => {
                        w.local.catalog.some((C) => b === C)
                          ? (console.log(b),
                            m.push({ version: b, type: "local" }),
                            (w.local.catalog = w.local.catalog.filter(
                              (C) => C !== b
                            )))
                          : m.push({ version: b, type: "online" });
                      }),
                        w.local.catalog.forEach((b) => {
                          m.push({ version: b, type: "local" });
                        }),
                        m.sort((b, C) =>
                          b.version > C.version
                            ? -1
                            : b.version < C.version
                            ? 1
                            : 0
                        ),
                        m.forEach((b) => {
                          b.type === "online"
                            ? (d += `<vscode-option><div><span slot="start" class="codicon codicon - globe"></span>${b.version}</div></vscode-option>`)
                            : (d += `<vscode-option><div><span slot="start" class="codicon codicon - folder "></span>${b.version}</div></vscode-option>`);
                        }),
                        console.log("optionsList", d),
                        this._panel.webview.postMessage({
                          type: s.type,
                          sdkOptions: d,
                        });
                    });

                  break;
                }
                case "projectHomePath": {
                  let n = te.Uri.file(
                    te.workspace
                      .getConfiguration()
                      .get(
                        i.Extension.Settings.projectHomeID,
                        te.ConfigurationTarget.Global
                      )
                      .toString()
                  );
                  console.log("projectHomePath", n.fsPath),
                    this._panel.webview.postMessage({
                      type: s.type,
                      projectHomePath: n.fsPath,
                    });
                  break;
                }
                case "getLanguageList": {
                  let n = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "python - logo.png"
                      )
                    ),
                    a = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "cpp - logo.png"
                      )
                    );
                  ae._languageOptionsList = [
                    {
                      languageTitle: "Python",
                      language: "python",
                      iconUri: n,
                      id: "0",
                    },
                    {
                      languageTitle: "C / C++",
                      language: "cpp",
                      iconUri: a,
                      id: "1",
                    },
                  ];
                  let r = Yt.getObjsFromOptionList(ae._languageOptionsList);
                  this._panel.webview.postMessage({
                    type: s.type,
                    html: Yt.html(r),
                  });
                  break;
                }
                case "getPlatformList": {
                  let n = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeEXP.png"
                      )
                    ),
                    a = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeIQGEN2.png"
                      )
                    ),
                    r = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeV5.png"
                      )
                    );
                  ae._platformOptionsList = [
                    {
                      platformName: "IQ 2n d Generation",
                      iconUri: a,
                      id: "0",
                      platform: "IQ2",
                    },
                    {
                      platformName: "EXP",
                      iconUri: n,
                      id: "1",
                      platform: "EXP",
                    },
                    {
                      platformName: "V5",
                      iconUri: r,
                      id: "2",
                      platform: "V5",
                    },
                  ];
                  let c = Qt.getObjsFromOptionList(ae._platformOptionsList);
                  this._panel.webview.postMessage({
                    type: s.type,
                    html: Qt.html(c),
                  });
                  break;
                }
                case "getProjectList": {
                  let n = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeEXP.png"
                      )
                    ),
                    a = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeIQGEN2.png"
                      )
                    ),
                    r = t.webview.asWebviewUri(
                      te.Uri.joinPath(
                        this._extensionUri,
                        "resources",
                        "icons",
                        "vexcodeV5.png"
                      )
                    ),
                    c = 0;
                  console.log(
                    ae._languageOptionsList[s.language_index].language,
                    ae._platformOptionsList[s.platform_index].platform
                  );
                  let l = Co.filter((m) =>
                    m.language ===
                      ae._languageOptionsList[s.language_index].language &&
                    m.platform ===
                      ae._platformOptionsList[s.platform_index].platform
                      ? 1
                      : 0
                  );
                  (ae._projectOptionsList = []),
                    l.forEach((m) => {
                      let w = {
                        description: m.description,
                        iconUri: m.iconUri,
                        language: m.language,
                        platform: m.platform,
                        projectName: m.projectName,
                        tags: m.tags,
                        zipName: m.zipName,
                        id: c.toString(),
                      };
                      if ((c++, w.iconUri)) {
                        let b = te.Uri.joinPath(
                          this._extensionUri,
                          "resources",
                          "icons",
                          w.iconUri.fsPath
                        );
                        (0, ds.existsSync)(Wi.resolve(b.fsPath))
                          ? (w.iconUri = t.webview.asWebviewUri(b))
                          : (w.iconUri = void 0);
                      }
                      m.iconUri === void 0 &&
                        (w.platform === "EXP" && (w.iconUri = n),
                        w.platform === "IQ2" && (w.iconUri = a),
                        w.platform === "V5" && (w.iconUri = r)),
                        ae._projectOptionsList.push(w);
                    });
                  let d = Ft.getObjsFromOptionList(ae._projectOptionsList);
                  this._panel.webview.postMessage({
                    type: s.type,
                    html: Ft.html(d),
                  });
                  break;
                }
                case "getProjectHtml": {
                  let n = ae._projectOptionsList.filter((r) =>
                      r.language ===
                        ae._languageOptionsList[s.language_index].language &&
                      r.platform ===
                        ae._platformOptionsList[s.platform_index].platform
                        ? 1
                        : 0
                    ),
                    a = Ft.getObjsFromOptionList([n[s.project_index]]);
                  this._panel.webview.postMessage({
                    type: s.type,
                    html: a[0].html,
                    language:
                      ae._languageOptionsList[s.language_index].language,
                  });
                  break;
                }
                case "getOSType": {
                  this._panel.webview.postMessage({
                    type: s.type,
                    osType: qs.type(),
                  });
                  break;
                }
                case "folderPath": {
                  let n = te.workspace
                    .getConfiguration()
                    .get(
                      i.Extension.Settings.projectHomeID,
                      te.ConfigurationTarget.Global
                    )
                    .toString();
                  this._panel.webview.postMessage({ type: s.type, path: n });
                }
              }
          }),
          t.onDidDispose(() => {
            ae._isRunning && (console.log("Disposed"), (o.event = "disposed")),
              (e = !0),
              (ae._isRunning = !1);
          });
        !e;

      )
        await new Promise((s) => setTimeout(s, 500));
      return console.log("Create Project DONE"), o;
    }
    static _getHtmlForWebview(t) {
      let e = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "dist",
            "webviews",
            "views",
            "newProject.js"
          )
        ),
        o = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "libs",
            "jquery",
            "jquery.js"
          )
        ),
        s = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "reset.css"
          )
        ),
        n = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "vscode.css"
          )
        ),
        a = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "main.css"
          )
        ),
        r = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "webview-ui-toolkit",
            "dist",
            "toolkit.js"
          )
        ),
        c = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.css"
          )
        ),
        l = t.asWebviewUri(
          te.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.svg"
          )
        ),
        d = Gi();
      return `<!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <!--
                        Use a content security policy to only allow loading images from https or from our extension directory,
                        and only allow scripts that have a specific nonce.
                    -->
                    <!--
                    <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${t.cspSource}; script-src 'nonce-${d}';">
                    --> 
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">

            
                    <link href="${s}" rel="stylesheet">
                    <link href="${a}"  rel="stylesheet">
                    <link href="${a}"  rel="stylesheet">
                    <link href="${c}"     rel="stylesheet">
                    
                    <script nonce="${d}" src="${o}"><\/script>
                    <script nonce="${d}" type="module" src="${r}"><\/script>
                    <script nonce="${d}" src="${e}"><\/script>


                    <title>Create new vex project</title>
                </head>
                <body>
                    <div id="mainForm" class="main-section noselect">
                        <div id="popUpWindow" class="main-popup-window">
                            <section  class="strectch-row">
                                <h2 id="contentTitle" class="h2-title">Create a New VEX Project</h2>
                                <section  class="top-strectch-row">
                                </section>
                                <vscode-button id="cancelBtn" appearance="icon" aria-label="Close">
                                    <i class="btnIcon codicon codicon-close"></i>
                                </vscode-button>							
                            </section>

                            <div class="component-container align-center">
                                <h3 id="contentInstruction" class="instruction-text">Select a Project Platform</h3>
                            </div>
                            <div id="search">
                                <section class="header-row">
                                    <vscode-text-field id="searchInput" placeHolder="Search">
                                        <span slot="start" class="codicon codicon-search"></span>
                                    </vscode-text-field>
                                </section>
                            </div>
                            <div id="contentWindow"  class="component-container project-list">
                            </div>
                            <section  class="strectch-column">
                            </section>
                            <section  class="button-row">
                                <section  class="button-row">
                                    <vscode-button id="createBtn" class="createBtn" appearance="primary"  aria-label="Create">
                                        Create
                                    </vscode-button>

                                </section>
                                <section  class="strectch-row">
                                </section>
                                <vscode-button id="backBtn" appearance="icon"  aria-label="Back">
                                <i class="btnIcon codicon codicon-arrow-left"></i>
                            </vscode-button>
                            </section>
                        </div>
                    </div>
                </body>
            </html>`;
    }
  },
  co = ae;
(co.viewType = "project.createNew"), (co._isRunning = !1);

function Gi() {
  let _ = "",
    t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let e = 0; e < 32; e++)
    _ += t.charAt(Math.floor(Math.random() * t.length));
  return _;
}
var ie = L(require("vscode"));
var Ks = L(require("os")),
  Qs = require("fs"),
  Ve = class {
    static async Show(t, e) {
      if (Ve._isRunning) {
        let n = ie.window.activeTextEditor
          ? ie.window.activeTextEditor.viewColumn
          : void 0;
        return (
          this._view.reveal(n || ie.ViewColumn.One),
          {
            event: "isRunning",
            projectPath: "",
            vexSettings: {
              extension: {
                version: "",
                json: 1,
              },
              project: {
                sdkVersion: "",
                creationDate: "",
                description: "",
                language: void 0,
                name: "",
                platform: void 0,
                slot: 1,
              },
            },
          }
        );
      }
      (Ve._isRunning = !0), (Ve._extensionUri = t);
      let o = ie.window.activeTextEditor
          ? ie.window.activeTextEditor.viewColumn
          : void 0,
        s = ie.window.createWebviewPanel(
          Ve.viewType,
          Ve._type,
          o || ie.ViewColumn.One
        );
      return await Ve.resolveWebviewView(s, e);
    }
    static async Reset() {
      (Ve._isRunning = !1), (Ve._eventDataRecieved = !0);
    }
    static async resolveWebviewView(t, e) {
      this._view = t;
      let o = {
        event: "disposed",
        vexSettings: e,
        projectPath: "",
      };
      for (
        t.webview.options = {
          enableScripts: !0,
          localResourceRoots: [
            ie.Uri.joinPath(Ve._extensionUri, "resources", "icons"),
            ie.Uri.joinPath(Ve._extensionUri, "resources", "webviews"),
            ie.Uri.joinPath(Ve._extensionUri, "dist", "webviews", "views"),
            ie.Uri.joinPath(
              Ve._extensionUri,
              "node_modules",
              "@vscode",
              "webview-ui-toolkit",
              "dist"
            ),
            ie.Uri.joinPath(
              Ve._extensionUri,
              "node_modules",
              "@vscode",
              "codicons",
              "dist"
            ),
            ie.Uri.joinPath(Ve._extensionUri, "resources", "webviews", "libs"),
            ie.Uri.joinPath(Ve._extensionUri, "resources", "webviews", "style"),
          ],
        },
          t.webview.html = await Ve._getHtmlForWebview(t.webview, e),
          t.webview.onDidReceiveMessage((s) => {
            switch (s.type) {
              case "cancelBtn": {
                (o.event = "cancel"), (o.vexSettings = void 0), t.dispose();
                break;
              }
              case "browseBtn": {
                console.log("browse btn clicked");
                let a = {
                  defaultUri: ie.Uri.file(ie.env.appHost),
                  canSelectFolders: !0,
                  canSelectFiles: !1,
                  canSelectMany: !1,
                };
                ie.window.showOpenDialog(a).then((r) => {
                  if ((console.log(r[0]), r[0] === void 0)) {
                    console.log("undefined file uri");
                    return;
                  }
                  this._view.webview.postMessage({
                    type: s.type,
                    path: r[0].fsPath,
                  });
                });
                break;
              }
              case "createProject": {
                console.log(s.simple_project_settings),
                  (o.event = "create"),
                  (o.vexSettings.project.name = s.simple_project_settings.name),
                  (o.vexSettings.project.description =
                    s.simple_project_settings.description),
                  (o.vexSettings.project.sdkVersion =
                    s.simple_project_settings.sdkVersion),
                  (o.projectPath = ie.Uri.joinPath(
                    ie.Uri.file(s.simple_project_settings.projectPath),
                    e.project.name
                  ).fsPath),
                  (o.vexSettings.extension.version = i.Extension.version()),
                  (o.vexSettings.project.creationDate =
                    new Date().toUTCString()),
                  t.dispose();
                break;
              }
              case "getOSType": {
                this._view.webview.postMessage({
                  type: s.type,
                  osType: Ks.type(),
                });
                break;
              }
              case "updateAndCheckFolderListAtPathFinal":
              case "updateAndCheckFolderListAtPath":
              case "updateFolderListAtPath": {
                if (!(0, Qs.existsSync)(s.path)) {
                  this._view.webview.postMessage({
                    type: s.type,
                    paths: [],
                  });
                  break;
                }
                console.log("Updated Folder List", s),
                  ie.workspace.fs
                    .readDirectory(ie.Uri.file(s.path))
                    .then((n) => {
                      let a = [];
                      console.log("Folder List", n),
                        n.forEach((r) => {
                          r[1] === ie.FileType.Directory && a.push(r[0]);
                        }),
                        console.log("Folder String List", a),
                        this._view.webview.postMessage({
                          type: s.type,
                          paths: a,
                        }),
                        console.log("Updated Folder List Finished ", s);
                    });
                break;
              }
              case "folderPath": {
                let n = ie.workspace
                  .getConfiguration()
                  .get(
                    i.Extension.Settings.projectHomeID,
                    ie.ConfigurationTarget.Global
                  )
                  .toString();
                this._view.webview.postMessage({
                  type: s.type,
                  path: n,
                });
              }
            }
          }),
          t.onDidDispose(() => {
            Ve._eventDataRecieved = !0;
          });
        !Ve._eventDataRecieved;

      )
        await new Promise((s) => setTimeout(s, 500));
      return (Ve._eventDataRecieved = !1), (Ve._isRunning = !1), o;
    }
    static async _getHtmlForWebview(t, e) {
      let o = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "dist",
            "webviews",
            "views",
            "projectSettings.js"
          )
        ),
        s = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "libs",
            "jquery",
            "jquery.js"
          )
        ),
        n = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "reset.css"
          )
        ),
        a = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "vscode.css"
          )
        ),
        r = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "main.css"
          )
        ),
        c = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "webview-ui-toolkit",
            "dist",
            "toolkit.js"
          )
        ),
        l = t.asWebviewUri(
          ie.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.css"
          )
        ),
        d = ie.Uri.file(
          ie.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.projectHomeID,
              ie.ConfigurationTarget.Global
            )
            .toString()
        ),
        m = ie.Uri.file(
          ie.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.sdkCPPHomeID,
              ie.ConfigurationTarget.Global
            )
            .toString()
        ),
        w = ie.Uri.file(
          ie.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.sdkPythonHomeID,
              ie.ConfigurationTarget.Global
            )
            .toString()
        ),
        b = ie.Uri.joinPath(d, e.project.name, "bin"),
        C;
      e.project.language === "python" &&
        (C = await i.Extension.ResourceManager.getSDKVersion(
          e.project.platform,
          e.project.language,
          w
        )),
        e.project.language === "cpp" &&
          (C = await i.Extension.ResourceManager.getSDKVersion(
            e.project.platform,
            e.project.language,
            m
          ));
      let E = JSON.parse(C.json);
      console.log(E);
      let T = [],
        O = "",
        f = "";
      Ve._type,
        (f = "Save"),
        E.online.catalog.forEach((z) => {
          E.local.catalog.some((Z) => z === Z)
            ? (console.log(z),
              z === e.project.sdkVersion
                ? T.unshift({
                    version: z,
                    type: "local",
                  })
                : T.push({
                    version: z,
                    type: "local",
                  }),
              (E.local.catalog = E.local.catalog.filter((Z) => Z !== z)))
            : z === e.project.sdkVersion
            ? T.unshift({
                version: z,
                type: "online",
              })
            : T.push({
                version: z,
                type: "online",
              });
        }),
        E.local.catalog.forEach((z) => {
          T.push({
            version: z,
            type: "local",
          });
        }),
        T.forEach((z) => {
          z.type === "online"
            ? (O += `<vscode-option><div><span slot="start" class="codicon codicon-globe"></span>${z.version}</div></vscode-option>`)
            : (O += `<vscode-option><div><span slot="start" class="codicon codicon-folder"></span>${z.version}</div></vscode-option>`);
        });
      let k = Ji();
      return `<!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <!--
                        Use a content security policy to only allow loading images from https or from our extension directory,
                        and only allow scripts that have a specific nonce.
                    -->
                    <!--
                    <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${t.cspSource}; script-src 'nonce-${k}';">
                    --> 
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">

            
                    <link href="${n}" rel="stylesheet">
                    <link href="${r}"  rel="stylesheet">
                    <link href="${r}"  rel="stylesheet">
                    <link href="${l}"     rel="stylesheet">
                    <script nonce="${k}" src="${s}"><\/script>
                    <script nonce="${k}" type="module" src="${c}"><\/script>
                    <script nonce="${k}" src="${o}"><\/script>


                    <title>${Ve._type}</title>
                </head>
                <body>
                    <div id="mainForm" class="main-section noselect">
                    <div id="popUpWindow" class="main-popup-window">
                        <section  class="strectch-row">
                            <h2 id="contentTitle" class="h2-title">VEX ${e.project.platform} Project ${Ve._type}</h2>
                            <section  class="strectch-row">
                            </section>
                            <vscode-button id="cancelBtn" appearance="icon" aria-label="Close">
                                <i class="btnIcon codicon codicon-close"></i>
                            </vscode-button>							
                        </section>
                        <div id="contentWindow"  class="component-container project-list">
                        <section class="component-container">
                        <div>Project Name</div>
                        <vscode-text-field id="projectNameInput" class="custom-textfield" placeHolder="myProjectName" value="${e.project.name}"></vscode-text-field>
                        <i id="projectName-infoText" > </i>
                
                        </section>
                        <section class="component-container"> 
                            <div>Description</div>
                            <vscode-text-area id="projectDescriptionInput" class="custom-textarea" placeHolder="Write your project description here . . ." value="${e.project.description}"></vscode-text-field>
                    
                        </section>
                        <section class="component-container">
                            <p>SDK Version</p>
                            <vscode-dropdown position="below" id="sdkDD">
                                ${O}
                            </vscode-dropdown>    
                        </section>
                        </div>
                        <section  class="strectch-column">
                        </section>
                        <section  class="button-row">
                            <section  class="button-row">
                                <vscode-button id="createBtn" class="createBtn" appearance="primary"  aria-label="Create">
                                    ${f}
                                </vscode-button>

                            </section>
                            <section  class="strectch-row">
                            </section>

                        </section>
                    </div>
                    </div>
                </body>
            </html>`;
    }
  },
  lt = Ve;
(lt.viewType = "project.createNew"),
  (lt._type = "Settings"),
  (lt._isRunning = !1),
  (lt._eventDataRecieved = !1);

function Ji() {
  let _ = "",
    t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let e = 0; e < 32; e++)
    _ += t.charAt(Math.floor(Math.random() * t.length));
  return _;
}
var ne = L(require("vscode"));
var Ys = L(require("os")),
  Zs = require("fs"),
  Ne = class {
    static get isRunning() {
      return Ne._isRunning;
    }
    static async Show(t, e, o = !0) {
      if (Ne._isRunning)
        return (
          this._panel.reveal(this._panel.viewColumn),
          {
            event: "isRunning",
            projectPath: "",
            vexSettings: {
              extension: {
                version: "",
                json: 1,
              },
              project: {
                sdkVersion: "",
                creationDate: "",
                description: "",
                language: void 0,
                name: "",
                platform: void 0,
                slot: 1,
              },
            },
          }
        );
      (Ne._isRunning = !0),
        (Ne._showProjectPathBrowser = o),
        (Ne._extensionUri = t);
      let s = ne.window.activeTextEditor
          ? ne.window.activeTextEditor.viewColumn
          : void 0,
        n = ne.window.createWebviewPanel(
          Ne.viewType,
          Ne._type,
          s || ne.ViewColumn.One
        );
      return await Ne.resolveWebviewView(n, e);
    }
    static async resolveWebviewView(t, e) {
      this._panel = t;
      let o = !1,
        s = {
          event: "disposed",
          vexSettings: e,
          projectPath: "",
        };
      for (
        t.webview.options = {
          enableScripts: !0,
          localResourceRoots: [
            ne.Uri.joinPath(Ne._extensionUri, "resources", "icons"),
            ne.Uri.joinPath(Ne._extensionUri, "resources", "webviews"),
            ne.Uri.joinPath(Ne._extensionUri, "dist", "webviews", "views"),
            ne.Uri.joinPath(
              Ne._extensionUri,
              "node_modules",
              "@vscode",
              "webview-ui-toolkit",
              "dist"
            ),
            ne.Uri.joinPath(
              Ne._extensionUri,
              "node_modules",
              "@vscode",
              "codicons",
              "dist"
            ),
            ne.Uri.joinPath(Ne._extensionUri, "resources", "webviews", "libs"),
            ne.Uri.joinPath(Ne._extensionUri, "resources", "webviews", "style"),
          ],
        },
          t.webview.html = await Ne._getHtmlForWebview(t.webview, e),
          t.webview.onDidReceiveMessage((n) => {
            switch (n.type) {
              case "cancelBtn": {
                (s.event = "cancel"), (s.vexSettings = void 0), t.dispose();
                break;
              }
              case "browseBtn": {
                console.log("browse btn clicked");
                let r = {
                  defaultUri: ne.Uri.file(ne.env.appHost),
                  canSelectFolders: !0,
                  canSelectFiles: !1,
                  canSelectMany: !1,
                };
                ne.window.showOpenDialog(r).then((c) => {
                  if ((console.log(c[0]), c[0] === void 0)) {
                    console.log("undefined file uri");
                    return;
                  }
                  this._panel.webview.postMessage({
                    type: n.type,
                    path: c[0].fsPath,
                  });
                });
                break;
              }
              case "createProject": {
                console.log(n.simple_project_settings),
                  (s.event = "create"),
                  (s.vexSettings.project.name = n.simple_project_settings.name),
                  (s.vexSettings.project.description =
                    n.simple_project_settings.description),
                  (s.vexSettings.project.sdkVersion =
                    n.simple_project_settings.sdkVersion),
                  (s.projectPath = ne.Uri.joinPath(
                    ne.Uri.file(n.simple_project_settings.projectPath),
                    e.project.name
                  ).fsPath),
                  (s.vexSettings.extension.version = i.Extension.version()),
                  (s.vexSettings.project.creationDate =
                    new Date().toUTCString()),
                  t.dispose();
                break;
              }
              case "getOSType": {
                this._panel.webview.postMessage({
                  type: n.type,
                  osType: Ys.type(),
                });
                break;
              }
              case "updateAndCheckFolderListAtPathFinal":
              case "updateAndCheckFolderListAtPath":
              case "updateFolderListAtPath": {
                if (!(0, Zs.existsSync)(n.path)) {
                  this._panel.webview.postMessage({
                    type: n.type,
                    paths: [],
                  });
                  break;
                }
                console.log("Updated Folder List", n),
                  ne.workspace.fs
                    .readDirectory(ne.Uri.file(n.path))
                    .then((a) => {
                      let r = [];
                      console.log("Folder List", a),
                        a.forEach((c) => {
                          c[1] === ne.FileType.Directory && r.push(c[0]);
                        }),
                        console.log("Folder String List", r),
                        this._panel.webview.postMessage({
                          type: n.type,
                          paths: r,
                        }),
                        console.log("Updated Folder List Finished ", n);
                    });
                break;
              }
              case "folderPath": {
                let a = ne.workspace
                  .getConfiguration()
                  .get(
                    i.Extension.Settings.projectHomeID,
                    ne.ConfigurationTarget.Global
                  )
                  .toString();
                this._panel.webview.postMessage({
                  type: n.type,
                  path: a,
                });
              }
            }
          }),
          t.onDidDispose(() => {
            o = !0;
          });
        !o;

      )
        await new Promise((n) => setTimeout(n, 500));
      return (o = !1), (Ne._isRunning = !1), s;
    }
    static async _getHtmlForWebview(t, e) {
      let o = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "dist",
            "webviews",
            "views",
            "importProject.js"
          )
        ),
        s = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "libs",
            "jquery",
            "jquery.js"
          )
        ),
        n = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "reset.css"
          )
        ),
        a = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "vscode.css"
          )
        ),
        r = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "main.css"
          )
        ),
        c = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "webview-ui-toolkit",
            "dist",
            "toolkit.js"
          )
        ),
        l = t.asWebviewUri(
          ne.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.css"
          )
        ),
        d = ne.Uri.file(
          ne.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.projectHomeID,
              ne.ConfigurationTarget.Global
            )
            .toString()
        ),
        m = ne.Uri.file(
          ne.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.sdkCPPHomeID,
              ne.ConfigurationTarget.Global
            )
            .toString()
        ),
        w = ne.Uri.file(
          ne.workspace
            .getConfiguration()
            .get(
              i.Extension.Settings.sdkPythonHomeID,
              ne.ConfigurationTarget.Global
            )
            .toString()
        ),
        b,
        C =
          e.project.platform === i.Platform.IQ2
            ? "IQ 2nd Generation"
            : e.project.platform;
      e.project.language === "python" &&
        (b = await i.Extension.ResourceManager.getSDKVersion(
          e.project.platform,
          e.project.language,
          w
        )),
        e.project.language === "cpp" &&
          (b = await i.Extension.ResourceManager.getSDKVersion(
            e.project.platform,
            e.project.language,
            m
          ));
      let E = "";
      Ne._type === "Import" && (E = "Import");
      let T = qi(),
        O = "";
      return (
        Ne._showProjectPathBrowser &&
          (O = `
            <div>Location</div>
            <section class="project-path-row">
                <vscode-text-field id="projectHomePathInput" class="custom-textfield" placeHolder="Path to my project" value="${d.fsPath}"></vscode-text-field>
                <vscode-button id="browseProjectPathBtn" class="space-left"  appearance="secondary">Browse</vscode-button>
            </section>
            `),
        `<!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <!--
                        Use a content security policy to only allow loading images from https or from our extension directory,
                        and only allow scripts that have a specific nonce.
                    -->
                    <!--
                    <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${t.cspSource}; script-src 'nonce-${T}';">
                    --> 
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">

            
                    <link href="${n}" rel="stylesheet">
                    <link href="${r}"  rel="stylesheet">
                    <link href="${l}"     rel="stylesheet">
                    <script nonce="${T}" src="${s}"><\/script>
                    <script nonce="${T}" type="module" src="${c}"><\/script>
                    <script nonce="${T}" src="${o}"><\/script>


                    <title>Import</title>
                </head>
                <body>
                    <div id="mainForm" class="main-section noselect">
                    <div id="popUpWindow" class="main-popup-window">
                        <section  class="strectch-row">
                            <h2 id="contentTitle" class="h2-title">VEX ${C} Project Import</h2>
                            <section  class="strectch-row">
                            </section>
                            <vscode-button id="cancelBtn" appearance="icon" aria-label="Close">
                                <i class="btnIcon codicon codicon-close"></i>
                            </vscode-button>							
                        </section>
                        <div id="contentWindow"  class="component-container project-list">
                        <section class="component-container">
                        <div>Project Name</div>
                        <vscode-text-field id="projectNameInput" class="custom-textfield" placeHolder="myProjectName" value="${e.project.name}"></vscode-text-field>
                        <i id="projectName-infoText" > </i>
                
                        </section>
                        <section class="component-container"> 
                            <div>Description</div>
                            <vscode-text-area id="projectDescriptionInput" class="custom-textarea" placeHolder="Write your project description here . . ." value="${e.project.description}"></vscode-text-field>
                    
                        </section>
                        <section class="component-container">
                        ${O}
                        <div id="infoText-projecHomePath" ></div>
                        </section>						
                        </div>
                        <section  class="strectch-column">
                        </section>
                        <section  class="button-row">
                            <section  class="button-row">
                                <vscode-button id="createBtn" class="createBtn" appearance="primary"  aria-label="Create">
                                    ${E}
                                </vscode-button>

                            </section>
                            <section  class="strectch-row">
                            </section>

                        </section>
                    </div>
                    </div>
                </body>
            </html>`
      );
    }
  },
  Vt = Ne;
(Vt.viewType = "project.createNew"),
  (Vt._type = "Import"),
  (Vt._isRunning = !1);

function qi() {
  let _ = "",
    t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let e = 0; e < 32; e++)
    _ += t.charAt(Math.floor(Math.random() * t.length));
  return _;
}
var Ki = !1,
  ei = new Map([
    ["280-7125", i.Platform.EXP],
    ["276-4810", i.Platform.V5],
    ["228-6480", i.Platform.IQ2],
  ]),
  Qi = new Map([
    ["Windows_NT_x32", "toolchain_win32"],
    ["Windows_NT_x64", "toolchain_win32"],
    ["Darwin_x32", "toolchain_osx64"],
    ["Darwin_x64", "toolchain_osx64"],
    ["Darwin_arm64", "toolchain_osxarm64"],
    ["Linux_x32", "toolchain_linux64"],
    ["Linux_x64", "toolchain_linux64"],
  ]),
  R = class {
    constructor(t, e) {
      this._projectList = [];
      this._processEnv = {};
      (R._context = t), this.On("Log", e), R._logHandler("Starting");
    }
    async setup() {
      (this._isBuilding = !1),
        (this._cppIntellisenseTemplateUri = $.Uri.joinPath(
          R._context.extensionUri,
          "resources",
          "templates",
          "settings",
          "c_cpp_properties.json"
        )),
        (this._pythonIntellisenseTemplateUri = $.Uri.joinPath(
          R._context.extensionUri,
          "resources",
          "templates",
          "settings",
          "settings.json"
        )),
        this._setOSSpecificProps(),
        await this._setDefaultUserSettings(),
        console.log(R._context.extensionUri),
        this.checkToolchain();
      let t = $.workspace
        .getConfiguration()
        .get(i.Extension.Settings.projectHomeID, $.ConfigurationTarget.Global)
        .toString();
      R._logHandler(`Project Home Path: ${t}`),
        R._logHandler(`Toolchain Home:    ${this._cppToolchainHomeUri.fsPath}`),
        R._logHandler(`Toolchain Path:    ${this._cppToolchainUri.fsPath}`),
        R._logHandler(`Sdk CPP    Home:   ${this._cppSdkHomeUri.fsPath}`),
        R._logHandler(`Sdk Python Home:   ${this._pythonSdkHomeUri.fsPath}`),
        this.searchForProjectsInWorkspace(),
        R._context.subscriptions.push(
          $.workspace.onDidChangeWorkspaceFolders((e) => {
            this._folderChange(e);
          })
        );
    }
    static getErrorMessageFromCode(t) {
      return R.buildErrorCodesDetails.get(t);
    }
    async build() {
      return (this._currentAction = "Build"), this._runMake();
    }
    async clean() {
      return (this._currentAction = "Clean"), this._runMake();
    }
    async rebuild() {
      let t = await this.clean();
      return t !== 0 || ((t = await this.build()), console.log(t)), t;
    }
    async newProject() {
      return (
        R._logHandler("New Project"),
        co.Show(R._context.extensionUri).then(async (t) => {
          switch ((console.log("New Project Response", t), t.event)) {
            case "cancel":
            case "disposed":
              console.log("Create Project Canceled", t),
                new Error("Create Project Canceled");
              break;
            case "isRunning":
              return "Create Project is Open Already";
            case "create":
              console.log("Create Project On Create", t),
                R._logHandler(`Template Zip:        ${t.zipName}`),
                R._logHandler(`New Project Path: ${t.projectPath}`),
                R._logHandler(
                  `Project Settings: ${JSON.stringify(t.vexSettings)}`
                );
              let e = $.Uri.joinPath(
                  $.Uri.file(t.projectPath),
                  t.vexSettings.project.name
                ),
                o = $.Uri.joinPath(
                  R._context.extensionUri,
                  "resources",
                  "templates",
                  "projects",
                  t.vexSettings.project.platform,
                  t.zipName
                ),
                s;
              xe.existsSync(e.fsPath) ||
                (await $.workspace.fs.createDirectory(e)),
                await i.Utils.unzipFile(o, e);
              let n = "";
              switch (t.vexSettings.project.language) {
                case "python":
                  (s = JSON.parse(
                    (
                      await i.Extension.ResourceManager.getSDKVersion(
                        t.vexSettings.project.platform,
                        t.vexSettings.project.language,
                        this._pythonSdkHomeUri
                      )
                    ).json
                  )),
                    (n = "py");
                  break;
                case "cpp":
                  (s = JSON.parse(
                    (
                      await i.Extension.ResourceManager.getSDKVersion(
                        t.vexSettings.project.platform,
                        t.vexSettings.project.language,
                        this._cppSdkHomeUri
                      )
                    ).json
                  )),
                    (n = "cpp");
                  let l = (await $.workspace.fs.readDirectory(e)).filter(
                    (m) => m[1] === $.FileType.File && m[0].includes(".v5code")
                  );
                  l.length &&
                    (await $.workspace.fs.delete($.Uri.joinPath(e, l[0][0])));
                  let d = this.getMakeEnvFile(e);
                  if (d < "2022_06_26_01" || d === "") {
                    let m = $.Uri.joinPath(e, "vex", "mkenv.mk");
                    await $.workspace.fs.delete(m, {
                      recursive: !1,
                      useTrash: !1,
                    });
                    let w = $.Uri.joinPath(
                      R._context.extensionUri,
                      "resources",
                      "templates",
                      "mk",
                      t.vexSettings.project.platform,
                      "mkenv_2022_06_26_01.mk"
                    );
                    await $.workspace.fs.copy(w, m, {
                      overwrite: !0,
                    });
                  }
                  break;
              }
              s.online.latest !== ""
                ? (t.vexSettings.project.sdkVersion = s.online.latest)
                : (t.vexSettings.project.sdkVersion = s.local.latest);
              let a = $.Uri.joinPath(e, "src", `main.${n}`),
                r = xe.readFileSync(a.fsPath, "utf8");
              xe.writeFileSync(
                a.fsPath,
                this._expandCommentHeaderData(r, a, t.vexSettings)
              ),
                await ht.writeProjectSettings(t.vexSettings, e),
                await this._createOrModifyGitIgnoreFile(e, t.vexSettings),
                await this._downloadSdkIfNotLocal(t.vexSettings),
                $.commands.executeCommand("vscode.openFolder", e);
              break;
          }
        })
      );
    }
    async importProject() {
      if (Vt.isRunning) {
        await Vt.Show(R._context.extensionUri, void 0);
        return;
      }
      let t = $.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.projectHomeID,
            $.ConfigurationTarget.Global
          ),
        e = $.Uri.file(t.toString()),
        o = {
          title: "Import Project",
          defaultUri: e,
          canSelectFolders: !1,
          canSelectFiles: !0,
          canSelectMany: !1,
          filters: {
            vexcode: R.importExtensions,
          },
        },
        s = await $.window.showOpenDialog(o);
      if ((console.log(s), !s?.length)) return "No File Selected";
      let n = s[0],
        a = $.Uri.file(He.dirname(n.fsPath)),
        r = He.basename(n.fsPath).split(".")[1];
      if (!xe.existsSync(n.fsPath))
        throw new Error("Project file does not exist");
      if (r === "zip") {
        let C = He.basename(n.fsPath, ".zip"),
          E = $.Uri.joinPath(R._context.extensionUri, "temp", C);
        await i.Utils.unzipFile(n, E),
          (await $.workspace.fs.readDirectory(E)).forEach((T) => {
            if (T[1] === $.FileType.File) {
              let O = T[0].split(".")[1],
                f = T[0] === "zip";
              R.importExtensions.includes(O) &&
                !f &&
                ((n = $.Uri.joinPath(E, T[0])), (r = O));
            }
          });
      }
      let c = [void 0, ""],
        l = !1,
        d = !0;
      switch (r) {
        case "v5code":
          (c[0] = this._v5code2ProjectSettings(n)), (c[1] = ""), (d = !1);
          break;
        case "v5cpp":
          c = this._v5cppToProjectSettings(n);
          break;
        case "v5python":
          c = this._v5pythonToProjectSettings(n);
          break;
        case "iqcpp":
          c = this._iq2cppToProjectSettings(n);
          break;
        case "iqpython":
          c = this._iq2pythonToProjectSettings(n);
          break;
        case "expcpp":
          c = this._expcppToProjectSettings(n);
          break;
        case "exppython":
          c = this._exppythonToProjectSettings(n);
          break;
        default:
          throw new Error(`Project ${He.basename(n.fsPath)}, not supported! `);
      }
      let m = await Vt.Show(R._context.extensionUri, c[0], d);
      if (m.event !== "create") return m.event;
      let w = $.Uri.file(He.dirname(n.fsPath)),
        b = $.Uri.file(m.projectPath);
      if (r.includes("code")) {
        let C = JSON.parse(
          (
            await i.Extension.ResourceManager.getSDKVersion(
              m.vexSettings.project.platform,
              m.vexSettings.project.language,
              this._cppSdkHomeUri
            )
          ).json
        );
        C.online.latest !== ""
          ? (m.vexSettings.project.sdkVersion = C.online.latest)
          : (m.vexSettings.project.sdkVersion = C.local.latest),
          (b = w);
        let E = this.getMakeEnvFile(b);
        if (E < "2022_06_26_01" || E === "") {
          let O = $.Uri.joinPath(b, "vex", "mkenv.mk");
          await $.workspace.fs.delete(O, {
            recursive: !1,
            useTrash: !1,
          });
          let f = $.Uri.joinPath(
            R._context.extensionUri,
            "resources",
            "templates",
            "mk",
            m.vexSettings.project.platform,
            "mkenv_2022_06_26_01.mk"
          );
          await $.workspace.fs.copy(f, O, {
            overwrite: !0,
          });
        }
        (await $.workspace.fs.readDirectory(b)).forEach((O) => {
          O[1] === $.FileType.File &&
            O[0].includes("compile_commands.json") &&
            xe.rmSync($.Uri.joinPath(b, O[0]).fsPath, {
              force: !0,
            }),
            O[1] === $.FileType.Directory &&
              O[0].includes("build") &&
              xe.rmSync($.Uri.joinPath(b, O[0]).fsPath, {
                recursive: !0,
                force: !0,
              });
        });
      } else if (r.includes("python")) {
        let C = JSON.parse(
          (
            await i.Extension.ResourceManager.getSDKVersion(
              m.vexSettings.project.platform,
              m.vexSettings.project.language,
              this._pythonSdkHomeUri
            )
          ).json
        );
        C.online.latest !== ""
          ? (m.vexSettings.project.sdkVersion = C.online.latest)
          : (m.vexSettings.project.sdkVersion = C.local.latest);
        let E = $.Uri.joinPath(
          R._context.extensionUri,
          "resources",
          "templates",
          "projects",
          m.vexSettings.project.platform,
          `py_${m.vexSettings.project.platform.toLowerCase()}_vsc_empty.zip`
        );
        console.log("Unzip Result: ", await i.Utils.unzipFile(E, b));
        let T = $.Uri.joinPath($.Uri.file(m.projectPath), "src", "main.py");
        await $.workspace.fs.delete(T),
          await $.workspace.fs.writeFile(T, new Xe.TextEncoder().encode(c[1]));
      } else if (r.includes("cpp")) {
        R._logHandler("Get SDK Info");
        let C = JSON.parse(
          (
            await i.Extension.ResourceManager.getSDKVersion(
              m.vexSettings.project.platform,
              m.vexSettings.project.language,
              this._cppSdkHomeUri
            )
          ).json
        );
        C.online.latest !== ""
          ? (m.vexSettings.project.sdkVersion = C.online.latest)
          : (m.vexSettings.project.sdkVersion = C.local.latest),
          R._logHandler("Unzip empty project");
        let E = $.Uri.joinPath(
          R._context.extensionUri,
          "resources",
          "templates",
          "projects",
          m.vexSettings.project.platform,
          `cpp_${m.vexSettings.project.platform.toLowerCase()}_vsc_empty.zip`
        );
        await i.Utils.unzipFile(E, b),
          R._logHandler("Delete template main.cpp");
        let T = $.Uri.joinPath($.Uri.file(m.projectPath), "src", "main.cpp");
        await $.workspace.fs.delete(T),
          R._logHandler("Write project text content to main.cpp"),
          await $.workspace.fs.writeFile(T, new Xe.TextEncoder().encode(c[1]));
      }
      await ht.writeProjectSettings(m.vexSettings, b),
        await this._createOrModifyGitIgnoreFile(b, m.vexSettings),
        await this._downloadSdkIfNotLocal(m.vexSettings),
        await $.commands.executeCommand("vscode.openFolder", b);
    }
    async showSettingsUI() {
      if (!this._selectedProject) throw new Error("No Project Selected");
      let t = this._selectedProject.lastProjectSettingsWrite;
      try {
        this._selectedProject.readProjectSettings();
      } catch (a) {
        R._logHandler(
          `Invalid Project Settings: Project ${this._selectedProject.name} @ ${this._selectedProject.settingsFileUri.fsPath}`
        ),
          R._logHandler(`Error: ${a.message}`),
          R._logHandler(""),
          R._logHandler("Trying to recreate . . . "),
          $.window.showWarningMessage(
            `Invalid Project Settings: Project ${this._selectedProject.name}, Recovering Settings`
          );
      }
      let e = await lt.Show(R._context.extensionUri, t);
      if (e.event !== "create") return;
      let o = this.getSDKHomeUriFromLanguage(e.vexSettings.project.language);
      if (!o)
        throw new Error(`Invalid Language: ${e.vexSettings.project.language}`);
      let s = await i.Extension.ResourceManager.getSDKVersion(
        e.vexSettings.project.platform,
        e.vexSettings.project.language,
        o
      );
      JSON.parse(s.json).local.catalog.includes(
        e.vexSettings.project.sdkVersion
      ) ||
        (await i.Extension.ResourceManager.downloadSDK(
          e.vexSettings.project.platform,
          e.vexSettings.project.language,
          e.vexSettings.project.sdkVersion,
          o
        )),
        await this._selectedProject.writeProjectSettings(e.vexSettings),
        this._updateProjectIntellesense(this._selectedProject);
    }
    On(t, e) {
      switch (t) {
        case "Build-Data":
          this._buildDataCB = e;
          break;
        case "Build-Errors":
          this._buildErrorCB = e;
          break;
        case "Build-Exit":
          this._buildExitCB = e;
          break;
        case "Log":
          R._logCB = e;
          break;
      }
    }
    get projectList() {
      return this._projectList;
    }
    get selectedProject() {
      return this._selectedProject;
    }
    set selectedProject(t) {
      this.projectList.includes(t) &&
        ($.commands
          .executeCommand(
            "setContext",
            `${i.Extension.id}.vexProjectSettingsFolderArr`,
            []
          )
          .then(() => {
            $.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexProjectSettingsFolderArr`,
              [this._selectedProject.settingsFileUri]
            );
          }),
        R._logHandler(`Selected Project: ${t.name}`),
        (this._selectedProject = t),
        this._updateProjectIntellesense(this._selectedProject));
    }
    get isBuilding() {
      return this._isBuilding;
    }
    getMakeEnvFile(t) {
      let e = $.Uri.joinPath(t, "vex", "mkenv.mk"),
        o = new Xe.TextDecoder().decode(xe.readFileSync(e.fsPath)),
        s = new RegExp(/(?<=\s*VEXcode\s*mkenv.mk\s*)\d{4}_\d{2}_\d{2}_\d{2}/);
      return s.test(o) ? s.exec(o)[0] : "";
    }
    async checkCppSdk(t) {
      R._logHandler("Checking for latest SDK-------------");
      let e = t.readProjectSettings(),
        o = await i.Extension.ResourceManager.getSDKVersion(
          e.project.platform,
          e.project.language,
          this._cppSdkHomeUri
        );
      R._logHandler("SDK Versions Recieved");
      let s = JSON.parse(o.json),
        n = s.online.latest !== "",
        a = s.local.latest !== "";
      s.online.catalog.forEach((m) => {
        R._logHandler(`Online SDK: ${m}`);
      }),
        s.local.catalog.forEach((m) => {
          R._logHandler(`Local SDK : ${m}`);
        });
      let r = "";
      if (n || a)
        if (e.project.sdkVersion === "")
          r = `Project ${t.name}: No SDK selected in project settings, would you like change the project settings?`;
        else {
          if (
            !s.local.catalog.includes(e.project.sdkVersion) &&
            e.project.sdkVersion === s.online.latest &&
            n
          )
            return (
              (r = `Project ${t.name}: SDK ${e.project.sdkVersion} does not exist, Downloading SDK ${s.online.latest} `),
              R._logHandler(`SDK Check Result: ${r}`),
              await this._downloadSdkIfNotLocal(t.readProjectSettings()),
              r
            );
          if (
            !s.local.catalog.includes(s.online.latest) &&
            n &&
            s.local.latest < e.project.sdkVersion
          )
            r = `Project ${t.name}: New SDK ${s.online.latest} available online, would you like to update project settings?`;
          else if (s.local.latest > e.project.sdkVersion)
            r = `Project ${t.name}: New SDK ${s.local.latest} available locally, would you like to update project settings?`;
          else if (!s.local.catalog.includes(e.project.sdkVersion) && n)
            r = `Project ${t.name}: SDK ${e.project.sdkVersion} does not exist, New SDK ${s.online.latest} available online, would you like to update project settings?`;
          else if (!s.local.catalog.includes(e.project.sdkVersion) && !n)
            r = `Project ${t.name}: SDK ${e.project.sdkVersion} does not exist, New SDK ${s.local.latest} available locally, would you like to update project settings?`;
          else
            return (
              R._logHandler(
                `SDK Found @: ${this._cppSdkHomeUri.fsPath} ver:${e.project.sdkVersion}`
              ),
              R._logHandler("SDK - Up To Date"),
              "SDK up to date"
            );
        }
      else
        throw new Error(
          "No Internet connection and no sdk availiable at current home directory"
        );
      R._logHandler(`SDK Check Result: ${r}`);
      let c = await $.window.showInformationMessage(r, "Settings", "Cancel");
      switch ((R._logHandler(`Project Settings Popup Click: ${c}`), c)) {
        case "Settings":
          break;
        case "Cancel":
          throw new Error("Cancel Clicked");
        case void 0:
          throw new Error("Cancel Clicked or Timedout");
        default:
          break;
      }
      let l = await lt.Show(R._context.extensionUri, e),
        d = l.vexSettings;
      switch (l.event) {
        case "isRunning":
          throw new Error("Create Project is Open Already");
        case "cancel":
        case "disposed":
          throw new Error("Cancel Clicked");
        case "create":
          await t.writeProjectSettings(d), await this._downloadSdkIfNotLocal(d);
          break;
      }
    }
    async _createOrModifyGitIgnoreFile(t, e) {
      let s = (await $.workspace.fs.readDirectory(t)).filter(
        (n) => n[0].includes(".gitignore") && n[1] === $.FileType.File
      );
      if (s.length) {
        console.log(s[0]);
        let n = $.Uri.joinPath(t, s[0][0]),
          a = xe.readFileSync(n.fsPath),
          r = new Xe.TextDecoder().decode(a),
          c = new RegExp(/(\\|\/|\s*|).vscode\s*/gi);
        c.test(r) &&
          (console.log(c.exec(r)),
          (r = r.replace(c, "")),
          xe.writeFileSync(n.fsPath, r, {
            encoding: "utf-8",
          }));
      } else {
        let n = $.Uri.joinPath(t, ".gitignore"),
          a = "";
        e.project.language === i.Language.cpp &&
          ((a += `/bin
`),
          (a += `/build
`),
          (a += `compile_commands.json
`)),
          xe.writeFileSync(n.fsPath, a, {
            encoding: "utf-8",
          });
      }
    }
    _updateProjectIntellesense(t) {
      switch (t.language) {
        case "python":
          t.updateIntellesenseJSON(this._pythonIntellisenseTemplateUri);
          break;
        case "cpp":
          t.updateIntellesenseJSON(this._cppIntellisenseTemplateUri);
          break;
      }
    }
    async _downloadSdkIfNotLocal(t) {
      let e = this.getSDKHomeUriFromLanguage(t.project.language);
      if (!e) throw new Error(`Invalid Language: ${t.project.language}`);
      let o = await i.Extension.ResourceManager.getSDKVersion(
        t.project.platform,
        t.project.language,
        e
      );
      if (!JSON.parse(o.json).local.catalog.includes(t.project.sdkVersion)) {
        let n = await i.Extension.ResourceManager.downloadSDK(
          t.project.platform,
          t.project.language,
          t.project.sdkVersion,
          e
        );
        n.statusCode === 200
          ? R._logHandler("Download SDK Finish")
          : R._logHandler(
              `Download Error - StatusCode:${n.statusCode} Details:${n.details}`
            );
      }
    }
    async checkPythonSdk(t) {
      R._logHandler("Checking for latest Stubs-------------");
      let e = t.readProjectSettings(),
        o = await i.Extension.ResourceManager.getSDKVersion(
          e.project.platform,
          e.project.language,
          this._pythonSdkHomeUri
        );
      R._logHandler("Stubs Versions Recieved");
      let s = JSON.parse(o.json),
        n = s.online.latest !== "",
        a = s.local.latest !== "";
      s.online.catalog.forEach((w) => {
        R._logHandler(`Online Stubs: ${w}`);
      }),
        s.local.catalog.forEach((w) => {
          R._logHandler(`Local Stubs : ${w}`);
        });
      let r = "",
        c = s.online.latest.split("_").slice(0, 5).join("_");
      if (n || a)
        if (e.project.sdkVersion === "")
          r = `Project ${t.name}: No Stubs selected in project settings, would you like project settings?`;
        else {
          if (
            !s.local.catalog.includes(e.project.sdkVersion) &&
            e.project.sdkVersion === s.online.latest &&
            n
          )
            return (
              (r = `Project ${t.name}: Sdk ${e.project.sdkVersion} does not exist, Downloading SDK ${s.online.latest} `),
              R._logHandler(`SDK Check Result: ${r}`),
              await this._downloadSdkIfNotLocal(t.readProjectSettings()),
              r
            );
          if (
            !s.local.catalog.includes(c) &&
            n &&
            s.local.latest < e.project.sdkVersion
          )
            r = `Project ${t.name}: New Sdk ${c} available online, would you like to update project settings?`;
          else if (s.local.latest > e.project.sdkVersion)
            r = `Project ${t.name}: New Sdk ${s.local.latest} available locally, would you like to update project settings?`;
          else if (!s.local.catalog.includes(c) && n)
            r = `Project ${t.name}: Sdk ${e.project.sdkVersion} does not exist, New SDK ${c} available online, would you like to update project settings?`;
          else if (!s.local.catalog.includes(e.project.sdkVersion) && !n)
            r = `Project ${t.name}: Sdk ${e.project.sdkVersion} does not exist, New SDK ${s.local.latest} available locally, would you like to update project settings?`;
          else
            return (
              R._logHandler(
                `Stubs Found @: ${this._pythonSdkHomeUri.fsPath} ver:${e.project.sdkVersion}`
              ),
              R._logHandler("Stubs - Up To Date"),
              "SDK up to date"
            );
        }
      else
        throw new Error(
          "No Internet connection and no Stubs availiable at current home directory"
        );
      R._logHandler(`SDK Check Result: ${r}`);
      let l = await $.window.showInformationMessage(r, "Settings", "Cancel");
      switch ((R._logHandler(`Project Settings Popup Click: ${l}`), l)) {
        case "Settings":
          break;
        case "Cancel":
          throw new Error("Cancel Clicked");
        case void 0:
          throw new Error("Cancel Clicked or Timedout");
        default:
          break;
      }
      let d = await lt.Show(R._context.extensionUri, e),
        m = d.vexSettings;
      switch (d.event) {
        case "isRunning":
          throw new Error("Create Project is Open Already");
        case "cancel":
        case "disposed":
          throw new Error("Cancel Clicked");
        case "create":
          await t.writeProjectSettings(m);
          break;
      }
      if (!s.local.catalog.includes(m.project.sdkVersion))
        if (
          (R._logHandler("Downloading Stubs"),
          (o = await i.Extension.ResourceManager.downloadSDK(
            m.project.platform,
            m.project.language,
            m.project.sdkVersion,
            this._pythonSdkHomeUri
          )),
          o.statusCode === 0)
        )
          R._logHandler("Download Stubs Finish");
        else
          throw new Error(
            `Download Error - StatusCode:${o.statusCode} Details:${o.details}`
          );
    }
    checkToolchain(t = !1) {
      R._logHandler("Checking if toolchain exist-------------"),
        !xe.existsSync(this._cppToolchainUri.fsPath) || t
          ? (R._logHandler(
              `Toolchain Not Found @: ${this._cppToolchainUri.fsPath}`
            ),
            R._logHandler(
              `Download Toolchain @: ${this._cppToolchainUri.fsPath}`
            ),
            i.Extension.ResourceManager.downloadToolchain(
              this._cppToolchainHomeUri
            ).then((e) => {
              R._logHandler(`Download Toolchain Finish: ${e.statusCode}`);
            }))
          : R._logHandler(`Toolchain Found @: ${this._cppToolchainUri.fsPath}`);
    }
    async _runMake() {
      R._logHandler(`${this._selectedProject.name}: Save All`),
        await $.workspace.saveAll(),
        this._selectedProject.updateProjectSettings();
      let t = this._getBuildArgs(),
        e = this._setUpBuildEnv();
      if (((this._isBuilding = !0), e !== 0)) {
        let s = `${R.buildErrorCodesDetails.get(e)} - ErrorCode: ${e}`,
          n = `${R.buildErrorCodesDetails.get(e)}`;
        throw (
          (this._buildErrorHandler(e, s),
          this._buildExitHandler(e),
          (this._isBuilding = !1),
          new Error(n))
        );
      }
      Ki &&
        (this._buildDataHandler(`\r
Build Args`),
        this._buildDataHandler(""),
        this._buildDataHandler(`OS:           ${Fe.type()}`),
        this._buildDataHandler(`Project Name: ${this.selectedProject.name}`),
        this._buildDataHandler(
          `Project Path: ${this.selectedProject.projectUri.fsPath}`
        ),
        this._buildDataHandler(`SDK:          ${this._cppSdkPathUri.fsPath}`),
        this._buildDataHandler(`Toochain:     ${this._cppToolchainUri.fsPath}`),
        this._buildDataHandler(`Make:         ${this._makeUri.fsPath}`),
        this._buildDataHandler(`GCC:          ${this._gccUri.fsPath}`),
        this._buildDataHandler(`Clang:        ${this._clangUri.fsPath}`),
        this._buildDataHandler(`CWD:          ${this._envOptions.cwd}`),
        this._buildDataHandler(`Build Args:   ${t}`),
        this._buildDataHandler("")),
        R._logHandler(
          `${this._selectedProject.name}: Build Type: ${this._currentAction}`
        ),
        R._logHandler(`${this._selectedProject.name}: Spawning Make Process`);
      let o = ti.spawn(this._makeUri.fsPath, t, {
        shell: !1,
        env: this._envOptions.env,
        cwd: this._envOptions.cwd,
      });
      for (
        console.log("Process Started"),
          o.stdout.on("data", (s) => {
            this._buildDataHandler(s);
          }),
          o.stderr.on("data", (s) => {
            this._buildErrorHandler(R.BuildErrorCodes.COMPILER_ERROR, s);
          }),
          o.on("exit", (s) => {
            this._buildExitHandler(s);
          });
        o.exitCode === null;

      )
        console.log(o.exitCode), await new Promise((s) => setTimeout(s, 500));
      return (
        (this._isBuilding = !1),
        console.log(`EXIT CODE: ${o.exitCode}`),
        R._logHandler(
          `${this._selectedProject.name}: Make Process EXIT CODE: ${o.exitCode}`
        ),
        o.exitCode
      );
    }
    _setUpBuildEnv() {
      if (!this._selectedProject) return R.BuildErrorCodes.NO_PROJECT_SELECTED;
      R._logHandler(`${this._selectedProject.name}: Setup Build Env`);
      let t = this._selectedProject.readProjectSettings(),
        e = He.delimiter;
      if (
        ((this._makeUri = $.Uri.joinPath(
          this._cppToolchainUri,
          "tools",
          "bin",
          this._makeName
        )),
        (this._gccUri = $.Uri.joinPath(this._cppToolchainUri, "gcc", "bin")),
        (this._clangUri = $.Uri.joinPath(
          this._cppToolchainUri,
          "clang",
          "bin"
        )),
        (this._cppSdkPathUri = $.Uri.joinPath(
          this._cppSdkHomeUri,
          t.project.platform,
          t.project.sdkVersion
        )),
        this._isBuilding)
      )
        return R.BuildErrorCodes.BUILD_ACTION_IN_PROCESS;
      if (!$.workspace.workspaceFolders.length)
        return R.BuildErrorCodes.NO_WORKSPACE_OPEN;
      if (!this._selectedProject.projectUri)
        return R.BuildErrorCodes.NOT_DEFINED_PROJECT;
      if (!xe.existsSync(this._selectedProject.projectUri.fsPath))
        return (
          console.log(this._selectedProject.projectUri.fsPath),
          R.BuildErrorCodes.PROJECT_PATH_DOES_NOT_EXIST
        );
      if (
        (R._logHandler(
          `${this._selectedProject.name}: Project Path: ${this._selectedProject.projectUri.fsPath}`
        ),
        !this._cppToolchainUri)
      )
        return R.BuildErrorCodes.NOT_DEFINED_TOOLCHAIN;
      if (!xe.existsSync(this._cppToolchainHomeUri.fsPath))
        return R.BuildErrorCodes.TOOLCHAIN_DOES_NOT_EXIST;
      if (
        (R._logHandler(
          `${this._selectedProject.name}: Toolchain Path: ${this._cppToolchainHomeUri.fsPath}`
        ),
        (!this._cppSdkPathUri && t.project.language === "cpp") ||
          t.project.sdkVersion === "")
      )
        return R.BuildErrorCodes.NOT_DEFINED_SDK;
      if (
        !xe.existsSync(this._cppSdkPathUri.fsPath) &&
        t.project.language === "cpp"
      )
        return R.BuildErrorCodes.MISSING_SDK;
      if (
        (R._logHandler(
          `${this.selectedProject.name}: SDK NAME: ${t.project.sdkVersion} SDK Path: ${this._cppSdkPathUri.fsPath}`
        ),
        !xe.existsSync(this._makeUri.fsPath))
      )
        return R.BuildErrorCodes.MAKE_DOES_NOT_EXIST;
      R._logHandler(
        `${this._selectedProject.name}: Make Path: ${this._makeUri.fsPath}`
      ),
        (this._processEnv.PATH = "");
      let o = new RegExp(/\$\{\s*workspaceFolder\s*\}/),
        s = new RegExp(/\$\{\s*workspaceFolderBasename\s*\}/),
        n = new RegExp(/\$\{\s*userHome\s*\}/),
        a = new RegExp(/\$\{\s*pathSeparator\s*\}/);
      return (
        this._selectedProject?.includeEnvUris?.length &&
          this._selectedProject.includeEnvUris.forEach((r) => {
            let c = r;
            o.test(c) &&
              (c = c.replace(o, this._selectedProject.projectUri.fsPath)),
              s.test(c) &&
                (c = c.replace(
                  s,
                  He.basename(this._selectedProject.projectUri.fsPath)
                )),
              n.test(c) && (c = c.replace(n, this._userHomeUri.fsPath)),
              a.test(c) && (c = c.replace(a, this._pathSeparator)),
              (this._processEnv.PATH += c + e);
          }),
        (this._processEnv.PATH += this._cppSdkPathUri.fsPath + e),
        (this._processEnv.PATH += this._gccUri.fsPath + e),
        (this._processEnv.PATH += this._clangUri.fsPath + e),
        (this._processEnv.PATH += process.env.PATH),
        (this._envOptions = {
          cwd: this._selectedProject.projectUri.fsPath,
          env: this._processEnv,
        }),
        R._logHandler(
          `${this._selectedProject.name}: EnvOptions: ${JSON.stringify(
            this._envOptions
          )}`
        ),
        R.BuildErrorCodes.NO_ERROR
      );
    }
    _getBuildArgs() {
      let t = this._selectedProject.readProjectSettings().project,
        e = [];
      switch (this._currentAction) {
        case "Build":
          e = [
            `P=${this._selectedProject.name.replace(" ", "_")}`,
            `T=${
              $.Uri.joinPath(this._cppSdkHomeUri, t.platform, t.sdkVersion)
                .fsPath
            }`,
            `OS=${Fe.type()}`,
          ];
          break;
        case "Clean":
          e = [
            "clean",
            `P=${this._selectedProject.name.replace(" ", "_")}`,
            `T=${
              $.Uri.joinPath(this._cppSdkHomeUri, t.platform, t.sdkVersion)
                .fsPath
            }`,
            `OS=${Fe.type()}`,
          ];
          break;
        case "Rebuild":
          break;
      }
      return (
        R._logHandler(`${this._selectedProject.name}: Build Args: ${e}`), e
      );
    }
    getSDKHomeUriFromLanguage(t) {
      let e;
      switch (t) {
        case "cpp":
          e = this._cppSdkHomeUri;
          break;
        case "python":
          e = this._pythonSdkHomeUri;
          break;
        default:
      }
      return e;
    }
    _setOSSpecificProps() {
      let t = new Xe.TextDecoder();
      Fe.type() === "Windows_NT"
        ? ((this._osEndLine = t.decode(new Uint8Array([13, 10]).buffer)),
          (this._makeName = "make.exe"),
          (this._compilerName = "clang.exe"),
          (this._userHomeUri = $.Uri.file(process.env.USERPROFILE)),
          (this._pathSeparator = "\\"))
        : Fe.type() === "Darwin"
        ? ((this._osEndLine = t.decode(new Uint8Array([13]).buffer)),
          (this._makeName = "make"),
          (this._compilerName = "clang"),
          (this._userHomeUri = $.Uri.file(process.env.HOME)),
          (this._pathSeparator = "/"))
        : (console.log(
            R._classType,
            new Error(`OS Not Recongnized: ${Fe.type()}`)
          ),
          R._logHandler(`OS Not Supported: ${Fe.type()}`),
          (this._osEndLine = t.decode(new Uint8Array([13]).buffer)),
          (this._makeName = "make"),
          (this._compilerName = "clang"),
          (this._userHomeUri = $.Uri.file(process.env.HOME)),
          (this._pathSeparator = "/")),
        R._logHandler(`Platform: ${Fe.type()}`),
        R._logHandler(`Arch: ${Fe.arch()}`),
        R._logHandler(
          `OS Endline: ${new Xe.TextEncoder().encode(this._osEndLine)}`
        ),
        R._logHandler(`Make  Type: ${this._makeName}`),
        R._logHandler(`Clang Type: ${this._compilerName}`);
    }
    async _setDefaultUserSettings() {
      R._logHandler("Setting Default User Settings");
      let t,
        e = $.workspace
          .getConfiguration()
          .get(i.Extension.Settings.projectHomeID, $.ConfigurationTarget.Global)
          .toString();
      console.log(R._classType, "Home Configuration", `${e}`),
        Fe.type() === "Darwin"
          ? (this._userName = process.env.USER)
          : Fe.type() === "Linux"
          ? (this._userName = process.env.USER)
          : (this._userName = process.env.USERNAME),
        e === "" &&
          (R._logHandler("Project Global Home Path Not Set"),
          Fe.type() === "Windows_NT"
            ? (t = $.Uri.joinPath(
                $.Uri.file(process.env.USERPROFILE),
                "Documents",
                "vex-vscode-projects"
              ))
            : Fe.type() === "Darwin"
            ? (t = $.Uri.joinPath(
                $.Uri.file(process.env.HOME),
                "Documents",
                "vex-vscode-projects"
              ))
            : Fe.type() === "Linux" &&
              (t = $.Uri.joinPath(
                $.Uri.file(process.env.HOME),
                "Documents",
                "vex-vscode-projects"
              )),
          console.log("OS Home URI", t),
          (e = t.fsPath),
          await $.workspace
            .getConfiguration()
            .update(
              i.Extension.Settings.projectHomeID,
              t.fsPath,
              $.ConfigurationTarget.Global
            ),
          xe.existsSync(t.path) || (await $.workspace.fs.createDirectory(t)));
      let o = `${Fe.type()}_${Fe.arch()}` ? `${Fe.type()}_${Fe.arch()}` : "";
      (this._cppToolchainHomeUri = $.Uri.joinPath(
        R._context.globalStorageUri,
        "tools",
        "cpp"
      )),
        (this._cppToolchainUri = $.Uri.joinPath(
          this._cppToolchainHomeUri,
          Qi.get(o)
        )),
        await $.workspace
          .getConfiguration()
          .update(
            i.Extension.Settings.toolchainCPPPathID,
            this._cppToolchainUri.fsPath,
            $.ConfigurationTarget.Global
          ),
        (this._cppSdkHomeUri = $.Uri.joinPath(
          R._context.globalStorageUri,
          "sdk",
          "cpp"
        )),
        await $.workspace
          .getConfiguration()
          .update(
            i.Extension.Settings.sdkCPPHomeID,
            this._cppSdkHomeUri.fsPath,
            $.ConfigurationTarget.Global
          ),
        xe.existsSync(this._cppSdkHomeUri.fsPath) ||
          (await $.workspace.fs.createDirectory(this._cppSdkHomeUri)),
        (this._pythonSdkHomeUri = $.Uri.joinPath(
          R._context.globalStorageUri,
          "sdk",
          "python"
        )),
        await $.workspace
          .getConfiguration()
          .update(
            i.Extension.Settings.sdkPythonHomeID,
            this._pythonSdkHomeUri.fsPath,
            $.ConfigurationTarget.Global
          ),
        xe.existsSync(this._pythonSdkHomeUri.fsPath) ||
          (await $.workspace.fs.createDirectory(this._pythonSdkHomeUri));
    }
    _expandCommentHeaderData(t, e, o) {
      let s = (m, w) => {
          let b = w.length + (w.length - m.length);
          if (m === "") return w;
          let C = w.length > m.length ? m.padEnd(b, " ") : m;
          return console.log("padHelper", C, w.length > m.length), C;
        },
        n = He.basename(e.fsPath),
        a = s(n, "{file}"),
        r = "{file}                ".slice(0, a.length);
      (t = t.replace(r, a)), (a = s(o.project.creationDate, "{date}"));
      let c = "{date}                ".slice(0, a.length);
      (t = t.replace(c, a)), (a = s(this._userName, "{author}"));
      let l = "{author}                                    ".slice(0, a.length);
      (t = t.replace(l, a)),
        (a = s(`${o.project.platform} project`, "{description}"));
      let d = "{description}                ".slice(0, a.length);
      return (t = t.replace(d, a)), t;
    }
    _v5code2ProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e)),
        s = ei.get(o.device.uid) ? o.device.uid : void 0,
        n = He.dirname(t.fsPath),
        a = $.Uri.file(n),
        r = $.Uri.joinPath(a, "vex", "mkenv.mk"),
        c = new Xe.TextDecoder().decode(xe.readFileSync(r.fsPath)),
        l = new RegExp(/(?<=PLATFORM\s*=\s*vex)(exp|v5|iq2)/),
        d = i.Platform.V5;
      l.test(c)
        ? (d = l.exec(c)[0].toUpperCase())
        : s && (d = ei.get(o.device.uid));
      let m = {
        project: {
          name: o.title,
          slot: o.device.slot ? o.device.slot : 1,
          description: o.description ? o.description : "",
          platform: d || i.Platform.V5,
          creationDate: "",
          language: o.language,
          sdkVersion: o.sdk,
          cpp: {
            includePath: [],
          },
        },
        extension: {
          version: i.Extension.version(),
          json: 1,
        },
      };
      if (!!m) return m;
    }
    _v5cppToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e)),
        s = {
          project: {
            name: He.basename(t.fsPath, ".v5cpp"),
            slot: o.slot ? o.slot : 1,
            description: "",
            platform: o.platform ? o.platform : i.Platform.V5,
            creationDate: "",
            language: o.textLanguage,
            sdkVersion: o.sdkVersion,
            cpp: {
              includePath: [],
            },
          },
          extension: {
            version: i.Extension.version(),
            json: 1,
          },
        };
      if (!!s) return [s, o.textContent];
    }
    _iq2cppToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e));
      if (o?.targetBrainGen !== "Second")
        throw Error(
          `${o.platform} ${o?.targetBrainGen} Gen Projects Not supported`
        );
      let s = {
        project: {
          name: He.basename(t.fsPath, ".iqcpp"),
          slot: o.slot ? o.slot : 1,
          description: "",
          platform: i.Platform.IQ2,
          creationDate: "",
          language: o.textLanguage,
          sdkVersion: o.sdkVersion,
          cpp: {
            includePath: [],
          },
        },
        extension: {
          version: i.Extension.version(),
          json: 1,
        },
      };
      if (!!s) return [s, o.textContent];
    }
    _expcppToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e)),
        s = {
          project: {
            name: He.basename(t.fsPath, ".expcpp"),
            slot: o.slot ? o.slot : 1,
            description: "",
            platform: o.platform ? o.platform : i.Platform.EXP,
            creationDate: "",
            language: o.textLanguage,
            sdkVersion: o.sdkVersion,
            cpp: {
              includePath: [],
            },
          },
          extension: {
            version: i.Extension.version(),
            json: 1,
          },
        };
      if (!!s) return [s, o.textContent];
    }
    _v5pythonToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o;
      try {
        o = JSON.parse(new Xe.TextDecoder().decode(e));
      } catch (n) {
        throw n;
      }
      let s = {
        project: {
          name: He.basename(t.fsPath, ".v5python"),
          slot: o.slot ? o.slot : 1,
          description: "",
          platform: o.platform ? o.platform : i.Platform.V5,
          creationDate: "",
          language: o.textLanguage,
          python: {
            main: $.Uri.joinPath($.Uri.file("src"), "main.py").fsPath,
          },
          sdkVersion: o.sdkVersion,
        },
        extension: {
          version: i.Extension.version(),
          json: 1,
        },
      };
      if (!!s) return [s, o.textContent];
    }
    _iq2pythonToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e));
      if (o?.targetBrainGen !== "Second")
        throw Error(
          `Import Failed: ${o.platform} ${o?.targetBrainGen} Gen Projects Not supported`
        );
      let s = {
        project: {
          name: He.basename(t.fsPath, ".iqpython"),
          slot: o.slot ? o.slot : 1,
          description: "",
          platform: i.Platform.IQ2,
          creationDate: "",
          language: o.textLanguage,
          python: {
            main: $.Uri.joinPath($.Uri.file("src"), "main.py").fsPath,
          },
          sdkVersion: o.sdkVersion,
        },
        extension: {
          version: "",
          json: 1,
        },
      };
      if (!!s) return [s, o.textContent];
    }
    _exppythonToProjectSettings(t) {
      let e = xe.readFileSync(t.fsPath),
        o = JSON.parse(new Xe.TextDecoder().decode(e)),
        s = {
          project: {
            name: He.basename(t.fsPath, ".exppython"),
            slot: o.slot ? o.slot : 1,
            description: "",
            platform: o.platform ? o.platform : i.Platform.EXP,
            creationDate: "",
            language: o.textLanguage,
            sdkVersion: o.sdkVersion,
            python: {
              main: $.Uri.joinPath($.Uri.file("src"), "main.py").fsPath,
            },
          },
          extension: {
            version: i.Extension.version(),
            json: 1,
          },
        };
      if (!!s) return [s, o.textContent];
    }
    searchForProjectsInWorkspace() {
      R._logHandler(""),
        R._logHandler("Looking for Projects in workspace ----------------");
      let t = $.workspace.workspaceFolders ? $.workspace.workspaceFolders : [];
      if (
        ((this._projectList = []),
        t.forEach((e) => {
          try {
            let o = $.Uri.joinPath(e.uri, ".vscode", ht.vexProjectSettingsName);
            if (!xe.existsSync(o.fsPath)) {
              R._logHandler(`WS Folder is not a VEX Project: ${e}`);
              return;
            }
            let s = ht.readProjectSettings(o);
            if (s) {
              let n = new ht(e.uri, s);
              this._projectList.push(n),
                R._logHandler(`Project found: ${n.name}`);
            }
          } catch (o) {
            console.log(
              R._classType,
              "Invalid Project Settings Error",
              e.name,
              e.uri,
              o
            ),
              R._logHandler(`Error adding project: ${e.name}, ${o}`);
          }
        }),
        this._projectList.length)
      ) {
        (this._selectedProject = this._selectedProject
          ? this._selectedProject
          : this._projectList[0]),
          $.commands
            .executeCommand(
              "setContext",
              `${i.Extension.id}.vexProjectSettingsFolderArr`,
              []
            )
            .then(() => {
              $.commands.executeCommand(
                "setContext",
                `${i.Extension.id}.vexProjectSettingsFolderArr`,
                [this._selectedProject.settingsFileUri]
              );
            }),
          this._updateProjectIntellesense(this._selectedProject);
        let e = this._selectedProject.readProjectSettings();
        e.project.language === "python"
          ? this.checkPythonSdk(this._selectedProject)
          : e.project.language === "cpp" &&
            this.checkCppSdk(this._selectedProject);
      } else R._logHandler("No VEX Projects found in workspace");
    }
    _buildDataHandler(t) {
      let e;
      console.log("Build Data CB", this._buildDataCB),
        typeof t == "string"
          ? (e = new Xe.TextEncoder().encode(t + this._osEndLine))
          : (e = t),
        this._buildDataCB && this._buildDataCB(e);
    }
    _buildErrorHandler(t, e) {
      let o;
      typeof e == "string"
        ? (o = new Xe.TextEncoder().encode(e + this._osEndLine))
        : (o = e),
        this._buildErrorCB && this._buildErrorCB(t, o);
    }
    _buildExitHandler(t) {
      this._buildExitCB && this._buildExitCB(t, this._currentAction);
    }
    static _logHandler(t) {
      let e = `${R._classType} ${t}`;
      R._logCB && R._logCB(e);
    }
    _folderChange(t) {
      console.log(
        R._classType,
        "Worspace Folder Change------------------------",
        t
      ),
        this.searchForProjectsInWorkspace();
    }
  },
  Ke = R;
(Ke._classType = "Project Manager: "),
  (Ke.importExtensions = [
    "v5code",
    "v5cpp",
    "iqcpp",
    "expcpp",
    "iqpython",
    "v5python",
    "exppython",
    "zip",
  ]);
((o) => {
  let _;
  ((T) => (
    (T[(T.NO_ERROR = 0)] = "NO_ERROR"),
    (T[(T.NO_WORKSPACE_OPEN = -10)] = "NO_WORKSPACE_OPEN"),
    (T[(T.MISSING_SDK = -11)] = "MISSING_SDK"),
    (T[(T.NOT_DEFINED_PROJECT = -12)] = "NOT_DEFINED_PROJECT"),
    (T[(T.NOT_DEFINED_TOOLCHAIN = -13)] = "NOT_DEFINED_TOOLCHAIN"),
    (T[(T.NOT_DEFINED_SDK = -14)] = "NOT_DEFINED_SDK"),
    (T[(T.PROJECT_PATH_DOES_NOT_EXIST = -15)] = "PROJECT_PATH_DOES_NOT_EXIST"),
    (T[(T.BUILD_ACTION_IN_PROCESS = -16)] = "BUILD_ACTION_IN_PROCESS"),
    (T[(T.MAKE_DOES_NOT_EXIST = -17)] = "MAKE_DOES_NOT_EXIST"),
    (T[(T.TOOLCHAIN_DOES_NOT_EXIST = -18)] = "TOOLCHAIN_DOES_NOT_EXIST"),
    (T[(T.NO_PROJECT_SELECTED = -19)] = "NO_PROJECT_SELECTED"),
    (T[(T.COMPILER_ERROR = -20)] = "COMPILER_ERROR")
  ))((_ = o.BuildErrorCodes || (o.BuildErrorCodes = {}))),
    (o.buildErrorCodesDetails = new Map([
      [-10, "No Workspace Folder is open"],
      [-11, "SDK not found"],
      [-12, "Project Folder not defined"],
      [-13, "Toolchain Folder not defined"],
      [-14, "SDK Path not defined"],
      [-15, "No Workspace Folder is open"],
      [-16, "Build action in progress"],
      [-17, "make.exe utillity doesn't not exist"],
      [-18, "toolchain does not exist"],
      [-19, "No Project Selected"],
      [-20, "Compiler Error"],
    ]));
  let e = !0;
})(Ke || (Ke = {}));
var M = L(require("vscode")),
  Zt = L(require("https")),
  be = L(require("fs")),
  ot = L(require("os"));
var ni = L(require("tar")),
  Oo = L(require("unzipper")),
  ai = L(require("etl")),
  Se = L(require("path")),
  dt = require("util"),
  Lo = require("child_process"),
  ci = L(require("tls")),
  tt = new Map([
    [100, "Continue"],
    [201, "Switching Protocols"],
    [202, "Processing"],
    [203, "Early Hints"],
    [200, "OK"],
    [201, "Created"],
    [203, "Non-Authoritative Information"],
    [204, "No Content"],
    [205, "Reset Content"],
    [206, "Partial Content"],
    [207, "Multi-Status"],
    [208, "Already Reported"],
    [226, "IM Used"],
    [300, "Multiple Choice"],
    [301, "Moved Permanently"],
    [302, "Found"],
    [303, "See Other"],
    [304, "Not Modified"],
    [305, "Use Proxy"],
    [306, "unused"],
    [307, "Temporary Redirect"],
    [308, "Permanent Redirect"],
    [400, "Bad Request"],
    [401, "Unauthorized"],
    [402, "Payment Required"],
    [403, "Forbidden"],
    [404, "Not Found"],
    [405, "Method Not Allowed"],
    [406, "Not Acceptable"],
    [407, "Proxy Authentication Required"],
    [408, "Request Timeout"],
    [409, "Conflict"],
    [410, "Gone"],
    [411, "Length Required"],
    [412, "Precondition Failed"],
    [413, "Payload To Large"],
    [414, "URI Too Long"],
    [415, "Unsupported Media Type"],
    [416, "Range Not Satisfiable"],
    [417, "Expectation Failed"],
    [418, "I'm a teapot"],
    [421, "Misdirected Request"],
    [422, "Unprocessable Entity"],
    [423, "Locked"],
    [424, "Failed Dependency"],
    [425, "Too Early"],
    [426, "Upgrade Required"],
    [428, "Precondition Required"],
    [429, "Too Many Requests"],
    [431, "Request Header Fields Too Large"],
    [451, "Unavailable For Lega Reasons"],
    [500, "Internal Server Error"],
    [501, "Not Implemented"],
    [502, "Bad Gateway"],
    [503, "Service Unavailable"],
    [504, "Gateway Timeout"],
    [505, "Http Version Not Supported"],
    [506, "Variant Also Negotiates"],
    [507, "Insufficient Storage"],
    [508, "Loop Detected"],
    [510, "Not Extended"],
    [511, "Network Authentication Required"],
  ]),
  ps = "catalog.txt",
  normal_manifest = "manifest.json",
  dev_manifest = "manifest-dev.json",
  ms = (_) => `https://content.vexrobotics.com/vexos/public/${_}/`,
  Zi = (_, t) =>
    `https://content.vexrobotics.com/vexos/public/${_}/vscode/sdk/${t}`,
  normal_manifest_url = (platform, language) =>
    `https://content.vexrobotics.com/vexos/public/${platform}/vscode/sdk/${language}/${normal_manifest}`,
  dev_manifest_url = (platform, language) =>
    `https://content.vexrobotics.com/vexos/public/${platform}/vscode/sdk/${language}/${dev_manifest}`,
  tr = (_, t, e) =>
    `https://content.vexrobotics.com/vexos/public/${_}/toolchain/${t}/${e}`,
  si = (_, t, e, o = "") =>
    `https://content.vexrobotics.com/vexai/${_}/apps/${t}/${e}${o}`,
  or = (_, t, e = "") =>
    `https://content.vexrobotics.com/vexai/${_}/apps/${t}${e}`,
  ii = (_, t, e = "") =>
    `https://content.vexrobotics.com/vexai/${_}/images/${t}${e}`,
  sr = (_, t) => `https://content.vexrobotics.com/vexcode/drivers/${_}/${t}`,
  ri = new Map([
    ["Windows_NT_x32", ["win", "toolchain_win32.zip"]],
    ["Windows_NT_x64", ["win", "toolchain_win32.zip"]],
    ["Darwin_x32", ["osx", "toolchain_osx32.zip"]],
    ["Darwin_x64", ["osx", "toolchain_osx64.zip"]],
    ["Darwin_arm64", ["osx", "toolchain_osxarm64.zip"]],
    ["Linux_x32", ["linux", "toolchain_linux64.zip"]],
    ["Linux_x64", ["linux", "toolchain_linux64.zip"]],
  ]),
  N = class {
    constructor(t, e) {
      this.On("Log", e),
        N._logHandler("Start"),
        (this._context = t),
        (this._showUiInfo = !0),
        this._defaultSDKPath,
        this._defaultToolchainPath;
    }
    async downloadToolChain(t) {
      N._logHandler("Download Toolchain");
      let e,
        o = t || M.Uri.joinPath(this._context.globalStorageUri, "tools", "cpp"),
        s = ri.get(`${ot.type()}_${ot.arch()}`)
          ? ri.get(`${ot.type()}_${ot.arch()}`)
          : [ot.type(), `toolchain_${ot.type()}${ot.arch()}.zip`],
        n = tr(N.ContentFolders.vscode, s[0], s[1]),
        a = M.Uri.joinPath(o, s[1]),
        r = M.Uri.joinPath(o, Se.basename(a.fsPath, ".zip"));
      N._logHandler(`Info:${ot.type()}_${ot.arch()}, ${s}`);
      let c = async (l, d) => {
        let m = await this._downloadHttpsFile(o, n, l, d);
        if ((console.log(`${m}: ${tt.get(m)}`), m !== 200))
          return (
            N._logHandler(`Download Error: ${m}`),
            M.window.showErrorMessage(`Download Error: ${m}`),
            m
          );
        if (be.existsSync(r.fsPath)) {
          N._logHandler(`Deleting old toolchain @ ${r.fsPath}`);
          let b = await M.workspace.fs.delete(r, {
            recursive: !0,
            useTrash: !1,
          });
          N._logHandler(`Deleting Result: ${b}}`);
        }
        let w = await N._unzipFile(a, void 0, l, d);
        return (
          await M.workspace.fs.delete(a, {
            recursive: !0,
            useTrash: !1,
          }),
          w
            ? (M.window.showErrorMessage(`Unzip Error: ${m}`), m)
            : (this.installToolchain(r), 0)
        );
      };
      if (this._showUiInfo) {
        let l = M.window.withProgress(
          {
            location: M.ProgressLocation.Notification,
            title: "",
            cancellable: !0,
          },
          async (d, m) => {
            (e = c(d, m)), await e;
          }
        );
      } else e = c();
    }
    async installToolchain(t, e, o) {
      let s = (n) => {
        N._logHandler(n),
          e &&
            e.report({
              message: n,
            });
      };
      if (
        (s("Installing Toolchain"),
        ot.type() === "Darwin" || ot.type() === "Linux")
      ) {
        console.log("toolchain URi", t);
        let n = M.Uri.joinPath(t, "clang", "bin"),
          a = M.Uri.joinPath(t, "gcc", "bin"),
          r = M.Uri.joinPath(t, "tools", "bin");
        console.log(
          "Path EXIST",
          be.existsSync(n.fsPath),
          be.existsSync(a.fsPath),
          be.existsSync(r.fsPath)
        ),
          (await M.workspace.fs.readDirectory(n)).forEach((c) => {
            N._logHandler(`File: ${c[0]}`),
              console.log(`File: ${c[0]}`),
              console.log(
                new dt.TextDecoder().decode(
                  (0, Lo.spawnSync)(`chmod +x ${c[0]}`, {
                    env: process.env,
                    cwd: n.fsPath,
                    shell: !0,
                  }).stderr
                )
              );
          }),
          (await M.workspace.fs.readDirectory(r)).forEach((c) => {
            N._logHandler(`File: ${c[0]}`),
              console.log(`File: ${c[0]}`),
              console.log(
                new dt.TextDecoder().decode(
                  (0, Lo.spawnSync)(`chmod +x ${c[0]}`, {
                    env: process.env,
                    cwd: r.fsPath,
                    shell: !0,
                  }).stderr
                )
              );
          }),
          (await M.workspace.fs.readDirectory(a)).forEach((c) => {
            N._logHandler(`File: ${c[0]}`),
              console.log(`File: ${c[0]}`),
              console.log(
                new dt.TextDecoder().decode(
                  (0, Lo.spawnSync)(`chmod +x ${c[0]}`, {
                    env: process.env,
                    cwd: a.fsPath,
                    shell: !0,
                  }).stderr
                )
              );
          });
      } else ot.type();
      s("Installing Finished");
    }
    async downloadVEXaiImage(t, e) {
      let o = N.ContentFolders.ai3d;
      N._logHandler(`Download VEX Image ${o}`);
      let s = require("os").homedir();
      console.log(s);
      let n = M.Uri.joinPath(
          M.Uri.file(s),
          `.${i.Extension.id}`,
          "vexai",
          o,
          "images"
        ),
        a = t ? M.Uri.joinPath(t, "vexai", o) : n,
        r,
        c = async (m, w) => {
          N._logHandler(`Platform: ${o}`), N._logHandler(`Location: ${t}`);
          let b = await this._getVEXaiImageVersionOnline(o);
          if (!b) return;
          let C = M.Uri.joinPath(a, `${b.latest}.tar.gz`);
          console.time("StreamRead");
          let E = await this._downloadHttpsFile(
            a,
            `${ii(o, b.latest, ".tar.gz")}`,
            m,
            w
          );
          if (
            (m.report({
              increment: -100,
              message: "",
            }),
            console.log(`${E}: ${tt.get(E)}`),
            E !== 200)
          )
            return (
              M.window.showErrorMessage(`${E}: ${tt.get(E)}`),
              await M.workspace.fs.delete(C, {
                recursive: !0,
                useTrash: !1,
              }),
              E
            );
          let T = M.Uri.joinPath(a, `${b.latest}.tar.gz`),
            O = M.Uri.joinPath(a, `${b.latest}`);
          be.existsSync(O.fsPath) ||
            (be.rmSync(O.fsPath, {
              force: !0,
              recursive: !0,
            }),
            be.mkdirSync(O.fsPath)),
            m.report({
              increment: -100,
              message: "",
            });
          let f = be.statSync(T.fsPath),
            k = be.createReadStream(T.fsPath);
          k.pipe(
            ni.x({
              cwd: O.fsPath,
            })
          ),
            k.on("error", (Z) => console.error(Z)),
            k.on("close", () => {
              k.destroy();
            });
          let z = 0;
          for (; !k.destroyed; ) {
            let Z = k.bytesRead,
              S = Z - z;
            (z = Z),
              m.report({
                increment: S / f.size,
                message: `Extracting:${Se.basename(T.fsPath)} ${(
                  (k.bytesRead / f.size) *
                  100
                ).toFixed(1)}%`,
              }),
              console.timeLog("StreamRead", `${k.bytesRead}B/${f.size}B`),
              await i.Utils.asyncSleep(250);
          }
          return (
            m.report({
              increment: -100,
              message: "",
            }),
            console.time("TimeEnd"),
            m.report({
              message: "UnTar Finished",
            }),
            0
          );
        },
        l = {
          report: e,
        },
        d;
      return (l.report = e), (r = c(l, d)), await r, r;
    }
    async getVEXaiImageVersions(t) {
      N._logHandler(""), N._logHandler("GET VEX AI VERSIONS");
      let e = N.ContentFolders.ai3d,
        o = {
          local: {
            latest: "",
            latest_priv: "",
            catalog: [],
            catalog_priv: [""],
          },
          online: {
            latest: "",
            latest_priv: "",
            catalog: [""],
            catalog_priv: [""],
          },
        };
      return (
        (o.online = await this._getVEXaiImageVersionOnline(e)),
        (o.local = await this._getVEXaiImageVersionsLocal(e, t)),
        N._logHandler(`Online: ${JSON.stringify(o.online)}`),
        N._logHandler(`Local : ${JSON.stringify(o.local)}`),
        o || {
          local: {
            latest: "",
            latest_priv: "",
            catalog: [],
            catalog_priv: [],
          },
          online: {
            latest: "",
            latest_priv: "",
            catalog: [],
            catalog_priv: [],
          },
        }
      );
    }
    async verifyVEXaiImage(t, e) {
      let o = M.Uri.joinPath(t, "manifest.json"),
        s = M.Uri.file(t.fsPath + ".tar.gz"),
        n = 0,
        a = 0,
        r,
        c = async (m, w) => {
          if (!be.existsSync(o.fsPath))
            return (
              await M.workspace.fs.delete(t),
              {
                checksum: "",
                errorCode: -3,
              }
            );
          let b = await M.workspace.fs.readFile(o),
            C = new dt.TextDecoder().decode(b),
            E = JSON.parse(C);
          m.report({
            increment: -100,
            message: "",
          });
          let T = E.files.length;
          for (let O = 0; O < E.files.length; O++) {
            let f = E.files[O],
              k = (S) => {
                let W = S / E.files.length,
                  V = W - n;
                (n = W),
                  (a += V),
                  S === 100 && (n = 0),
                  V > 0 &&
                    m.report({
                      increment: V,
                      message: "Verifying Local Image:",
                    });
              },
              z = M.Uri.file(Se.resolve(t.fsPath, f.path)),
              Z = await i.Utils.getMd5FromFile(z, "hex", {
                cb: k,
                updateTimeMs: 100,
              });
            if (
              (m.report({
                increment: 0,
                message: "",
              }),
              Z.checksum !== f.checksum)
            )
              return (
                be.existsSync(s.fsPath) &&
                  (await M.workspace.fs.delete(s, {
                    recursive: !0,
                    useTrash: !1,
                  })),
                await M.workspace.fs.delete(t, {
                  recursive: !0,
                  useTrash: !1,
                }),
                Z
              );
            T--;
          }
          return (
            be.existsSync(s.fsPath) &&
              (await M.workspace.fs.delete(s, {
                recursive: !0,
                useTrash: !1,
              })),
            {
              checksum: "",
              errorCode: 0,
            }
          );
        },
        l = {
          report: () => {},
        },
        d;
      return (l.report = e), (r = c(l, d)), r;
    }
    async getVEX3DaiAppListVersions(t) {
      N._logHandler(""), N._logHandler("GET VEX AI VERSIONS");
      let e = N.ContentFolders.ai3d,
        o = {
          online: {
            apps: [],
          },
          local: {
            apps: [],
          },
        };
      return (
        (o.online = await this._getVEXaiAppListOnline(e)),
        (o.local = await this._getVEXaiAppListLocal(e, t)),
        o || {
          local: {
            apps: [],
          },
          online: {
            apps: [],
          },
        }
      );
    }
    async getVEXaiAppManifest(t, e) {
      N._logHandler(""), N._logHandler("GET VEX AI VERSIONS");
      let o = N.ContentFolders.ai3d,
        s = {
          online: {
            latest: "",
            catalog: [],
          },
          local: {
            latest: "",
            catalog: [],
          },
        };
      return (
        (s.online = await this._getVEXaiAppManifestOnline(o, t)),
        (s.local = await this._getVEXaiAppVersionLocal(o, t, e)),
        s || {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
            catalog: [],
          },
        }
      );
    }
    async downloadVEXaiApp(t, e) {
      let o = N.ContentFolders.ai3d;
      N._logHandler("Download VEX AI App");
      let s = require("os").homedir(),
        n = M.Uri.joinPath(
          M.Uri.file(s),
          `.${i.Extension.id}`,
          "vexai",
          o,
          "apps"
        ),
        a = e || n,
        r = si(o, t.split("_")[0], t, ".deb"),
        c,
        l = async (d, m) => {
          let w = await this._downloadHttpsFile(a, `${r}`, d, m);
          if ((console.log(`${w}: ${tt.get(w)}`), w !== 200)) return w;
        };
      if (this._showUiInfo) {
        let d = M.window.withProgress(
          {
            location: M.ProgressLocation.Notification,
            title: "Downloading VEXOS",
            cancellable: !0,
          },
          async (m, w) => {
            (c = l(m, w)), await c;
          }
        );
      } else c = l();
      return c;
    }
    async downloadVEXosFile(t, e) {
      N._logHandler("Download VEXOS");
      let o = e || M.Uri.joinPath(this._context.globalStorageUri, "vexos", t),
        s = ms(t),
        n,
        a = async (r, c) => {
          let l = await this._readHttpsFile(`${ms(t)}${ps}`);
          if (
            (console.log(`${l.httpsCode}: ${tt.get(l.httpsCode)}`),
            l.httpsCode !== 200)
          )
            return l.httpsCode;
          let d = new dt.TextDecoder("UTF-8").decode(l.buf);
          d += ".vexos";
          let m = await this._downloadHttpsFile(o, `${s}/${d}`, r, c);
          if ((console.log(`${m}: ${tt.get(m)}`), m !== 200)) return m;
        };
      if (this._showUiInfo) {
        let r = M.window.withProgress(
          {
            location: M.ProgressLocation.Notification,
            title: "Downloading VEXOS",
            cancellable: !0,
          },
          async (c, l) => {
            (n = a(c, l)), await n;
          }
        );
      } else n = a();
      return n;
    }
    async getLatestVEXosManifest(t, e) {
      N._logHandler(""), N._logHandler("GET VEXOS Manifest");
      let o = t || N.ContentFolders.exp,
        s = {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
          },
        },
        n = {
          version: "",
          build: "",
          bootloader: {
            version: "",
            file: "",
          },
          ctrl: {
            radio: {
              version: "",
              file: "",
            },
            cdc: {
              version: "",
              file: "",
            },
          },
        },
        a = {
          version: "",
          build: "",
          vision: {
            version: "",
          },
          golden: !0,
        },
        r = "";
      switch (t) {
        case N.ContentFolders.v5:
          return (
            (s.local = await this._getVEXOSVersionsLocal(o, e)),
            (r = await this._getVEXOSManaifestLocal(o, e, s.local.latest)),
            N._logHandler(`${s.local.latest} Manifest: ${r}`),
            JSON.parse(r)
          );
        case N.ContentFolders.exp:
        case N.ContentFolders.iq2:
          return (
            (s.local = await this._getVEXOSVersionsLocal(o, e)),
            (r = await this._getVEXOSManaifestLocal(o, e, s.local.latest)),
            N._logHandler(`${s.local.latest} Manifest: ${r}`),
            JSON.parse(r)
          );
        default:
          return JSON.parse("{}");
      }
      return (
        N._logHandler(`Online: ${JSON.stringify(s.online)}`),
        N._logHandler(`Local : ${JSON.stringify(s.local)}`),
        s || {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
          },
        }
      );
    }
    async getVEXosVersions(t, e) {
      N._logHandler(""), N._logHandler("GET VEXOS VERSIONS");
      let o = t || N.ContentFolders.exp,
        s = {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
          },
        };
      return (
        (s.online.latest = await this._getVEXOSVersionOnline(o)),
        (s.local = await this._getVEXOSVersionsLocal(o, e)),
        N._logHandler(`Online: ${JSON.stringify(s.online)}`),
        N._logHandler(`Local : ${JSON.stringify(s.local)}`),
        s || {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
          },
        }
      );
    }
    async downloadSDK(platform, language, version, path) {
      N._logHandler("Download SDK");
        // Example for V5:
        // platform = V5
        // language = cpp
        // version = V5_20220726_10_00_00
        // path = vscode-userdata:/home/chez/.config/VSCodium/User/globalStorage/vexrobotics.vexcode/sdk/cpp

      let save_path = path
          ? M.Uri.joinPath(path, platform)
          : M.Uri.joinPath(this._context.globalStorageUri, "sdk", language),
        a = Zi(platform, language),
        r,
        c = async (l, d) => {
          N._logHandler(`Platform: ${platform}`),
            N._logHandler(`Version: ${version}`),
            N._logHandler(`Location: ${path}`);
          let w = (await this._getManifestVersionOnline(platform, language)).catalog.filter(
              (O) => O.includes(version)
            ),
            b = w.length
              ? w[0]
              : (await this._getManifestVersionOnline(platform, language)).latest,
            C = M.Uri.joinPath(save_path, `${b}.zip`),
            E = await this._downloadHttpsFile(save_path, `${a}/${b}.zip`, l, d);
          return (
            console.log(`${E}: ${tt.get(E)}`),
            E !== 200
              ? (M.window.showErrorMessage(`${E}: ${tt.get(E)}`),
                await M.workspace.fs.delete(C, {
                  recursive: !0,
                  useTrash: !1,
                }),
                E)
              : (await N._unzipFile(C, void 0, l, d))
              ? (M.window.showErrorMessage(`Unzip Error: ${E}`), E)
              : (await M.workspace.fs.delete(C, {
                  recursive: !0,
                  useTrash: !1,
                }),
                be.existsSync(M.Uri.joinPath(save_path, "__MACOSX").fsPath) &&
                  (await M.workspace.fs.delete(M.Uri.joinPath(save_path, "__MACOSX"), {
                    recursive: !0,
                    useTrash: !1,
                  })),
                E)
          );
        };
      if (this._showUiInfo) {
        let l = M.window.withProgress(
          {
            location: M.ProgressLocation.Notification,
            title: "",
            cancellable: !0,
          },
          async (d, m) => {
            (r = c(d, m)), await r;
          }
        );
      } else r = c();
      return r;
    }
    async getSDKVersions(t, e, o) {
      N._logHandler("Get SDK Versions");
      let s = t || N.ContentFolders.exp,
        n = {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
            catalog: [],
          },
        };
      return (
        (n.online = await this._getManifestVersionOnline(s, e)),
        (n.local = await this._getManifestVersionLocal(
          s,
          N.ManifestType.sdk,
          o
        )),
        N._logHandler(`SDK Online: ${JSON.stringify(n.online)}`),
        N._logHandler(`SDK Local: ${JSON.stringify(n.local)}`),
        n || {
          local: {
            latest: "",
            catalog: [],
          },
          online: {
            latest: "",
            catalog: [],
          },
        }
      );
    }
    async downloadDriverInstaller(t, e) {
      N._logHandler("Download Driver Installer");
      let o = e
          ? M.Uri.joinPath(e)
          : M.Uri.joinPath(this._context.globalStorageUri, "drivers"),
        s = t || " ",
        n = sr(s, "VEX Devices Driver Installer.exe"),
        a,
        r = async (c, l) => {
          N._logHandler(`Location: ${o.fsPath}`);
          let d = M.Uri.joinPath(o, s),
            m = await this._downloadHttpsFile(o, `${n}`, c, l);
          return (
            console.log(`${m}: ${tt.get(m)}`),
            m !== 200 &&
              (M.window.showErrorMessage(`${m}: ${tt.get(m)}`),
              await M.workspace.fs.delete(d, {
                recursive: !0,
                useTrash: !1,
              })),
            m
          );
        };
      if (this._showUiInfo) {
        let c = M.window.withProgress(
          {
            location: M.ProgressLocation.Notification,
            title: "",
            cancellable: !0,
          },
          async (l, d) => {
            (a = r(l, d)), await a;
          }
        );
      } else a = r();
      return a;
    }
    async _getManifestVersionLocal(t, e, o) {
      N._logHandler(`Get ${e} Manifest Versions Local`),
        N._logHandler(`Platform: ${t}`),
        N._logHandler(`Search Location: ${o.fsPath}`),
        console.log("Local Uri", o);
      let s = M.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "build",
          e,
          t
        ),
        n = o ? M.Uri.joinPath(o, t) : s,
        a = [];
      be.existsSync(n.fsPath) && (a = await M.workspace.fs.readDirectory(n));
      let r = {
          latest: "",
          catalog: [],
        },
        c = a.filter((l) => l[0].includes(t) && l[1] === M.FileType.Directory);
      return (
        console.log("Local Filtered", a, c, t),
        c.forEach((l) => {
          r.catalog.push(l[0]);
        }),
        r.catalog.sort(N._sortSDKListCB),
        (r.latest = r.catalog[0] ? r.catalog[0] : ""),
        r
      );
    }
    async _getManifestVersionOnline(platform, language) {
      N._logHandler(`Get ${language} SDK Version Online`),
        N._logHandler(`Platform: ${platform}`);
      let o = M.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "build",
          "sdk",
          language,
          platform
        ),
        s = M.Uri.joinPath(o, normal_manifest),
        n = i.Extension.Context.isDevEnabled ? dev_manifest_url(platform, language) : normal_manifest_url(platform, language),
        a = {
          latest: "",
          catalog: [],
        },
        r = await this._readHttpsFile(n);
      return (
        N._logHandler(`${r.httpsCode}: ${tt.get(r.httpsCode)}`),
        (r.httpsCode !== 200 && !i.Extension.Context.isDevEnabled) ||
        (r.httpsCode !== 200 &&
          i.Extension.Context.isDevEnabled &&
          ((r = await this._readHttpsFile(normal_manifest_url(platform, language))),
          N._logHandler(`${r.httpsCode}: ${tt.get(r.httpsCode)}`),
          r.httpsCode !== 200 && !i.Extension.Context.isDevEnabled))
          ? a
          : ((a = JSON.parse(new dt.TextDecoder("UTF-8").decode(r.buf))),
            console.log(a),
            a.catalog.sort(N._sortSDKListCB),
            a || { latest: "", catalog: [""] })
      );
    }
    async _getVEXOSManaifestLocal(t, e, o) {
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${e.fsPath}`);
      let s = M.Uri.joinPath(e, t, o + ".vexos"),
        n = async () => {
          let r,
            c = !1;
          for (
            be
              .createReadStream(s.fsPath)
              .on("error", (l) => {
                console.log(l), (c = !0);
              })
              .pipe(Oo.Parse())
              .pipe(
                ai.map(async (l) => {
                  l.path.includes("manifest.json")
                    ? l.buffer().then((d) => {
                        console.log(d), (r = d), (c = !0);
                      })
                    : l.autodrain();
                })
              );
            !c;

          )
            await new Promise((l) => setTimeout(l, 500));
          return r;
        };
      return new dt.TextDecoder().decode(await n());
    }
    async _getVEXOSVersionsLocal(t, e) {
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${e.fsPath}`);
      let o = M.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "vexos",
          t
        ),
        s = e ? M.Uri.joinPath(e, t) : o,
        n = [];
      be.existsSync(s.fsPath) && (n = await M.workspace.fs.readDirectory(s));
      let a = { latest: "", catalog: [] };
      return (
        n
          .filter(
            (c) =>
              c[0].includes(t) &&
              c[0].includes(".vexos") &&
              c[1] === M.FileType.File
          )
          .forEach((c) => {
            a.catalog.push(Se.basename(c[0], ".vexos"));
          }),
        a.catalog.sort(N._sortVEXOSListCB),
        (a.latest = a.catalog[0] ? a.catalog[0] : ""),
        a
      );
    }
    async _getVEXOSVersionOnline(t) {
      let e = M.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "vexos",
          t
        ),
        o = M.Uri.joinPath(e, ps),
        s = ms(t),
        n = await this._readHttpsFile(`${s}${ps}`);
      if (n.httpsCode !== 200) return "";
      let a = new dt.TextDecoder("UTF-8").decode(n.buf);
      return a || "";
    }
    async _getVEXaiImageVersionOnline(t) {
      let e = ii(t, normal_manifest),
        o = await this._readHttpsFile(`${e}`);
      if (o.httpsCode !== 200)
        return { latest: "", latest_priv: "", catalog: [""], catalog_priv: [] };
      let s = new dt.TextDecoder("UTF-8").decode(o.buf),
        n = JSON.parse(s);
      return (
        console.log(n),
        n.catalog.sort(N._sortSDKListCB),
        n || { latest: "", catalog: [""] }
      );
    }
    async _getVEXaiAppListOnline(t) {
      let e = or(t, normal_manifest),
        o = await this._readHttpsFile(`${e}`);
      if (o.httpsCode !== 200) return { apps: [] };
      let s = new dt.TextDecoder("UTF-8").decode(o.buf),
        n = JSON.parse(s);
      return console.log(n), n || { apps: [] };
    }
    async _getVEXaiAppListLocal(t, e) {
      let o = require("os").homedir();
      console.log(o);
      let s = M.Uri.joinPath(M.Uri.file(o), `.${i.Extension.id}`, t, "apps"),
        n = e ? M.Uri.joinPath(e, t, "apps") : s,
        a = [];
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${s?.fsPath}`),
        be.existsSync(n.fsPath) && (a = await M.workspace.fs.readDirectory(n));
      let r = { apps: [] };
      return (
        a
          .filter((l) => l[1] === M.FileType.File && l[0].includes(".deb"))
          .forEach((l) => {
            r.apps.push(l[0]);
          }),
        r
      );
    }
    async _getVEXaiAppVersionLocal(t, e, o) {
      let s = require("os").homedir();
      console.log(s);
      let n = M.Uri.joinPath(M.Uri.file(s), `.${i.Extension.id}`, t, "apps"),
        a = o ? M.Uri.joinPath(o, t, "apps") : n,
        r = [];
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${n?.fsPath}`),
        be.existsSync(a.fsPath) && (r = await M.workspace.fs.readDirectory(a));
      let c = { catalog: [], latest: "" };
      return (
        r
          .filter(
            (d) =>
              d[1] === M.FileType.File &&
              d[0].includes(".deb") &&
              d[0].includes(e)
          )
          .forEach((d) => {
            c.catalog.push(Se.basename(d[0], ".deb"));
          }),
        c.catalog.sort(N._sortSDKListCB),
        (c.latest = c.catalog[0] ? c.catalog[0] : ""),
        c
      );
    }
    async _getVEXaiAppManifestOnline(t, e) {
      let o = si(t, e, normal_manifest),
        s = await this._readHttpsFile(`${o}`);
      if (s.httpsCode !== 200) return { latest: "", catalog: [] };
      let n = new dt.TextDecoder("UTF-8").decode(s.buf),
        a = JSON.parse(n);
      return console.log(a), a || { latest: "", catalog: [] };
    }
    async _getVEXaiAppManifestLocal(t, e, o) {
      let s = require("os").homedir();
      console.log(s);
      let n = M.Uri.joinPath(
          M.Uri.file(s),
          `.${i.Extension.id}`,
          "vexai",
          t,
          "apps"
        ),
        a = o ? M.Uri.joinPath(o, "vexai", t) : n,
        r = [];
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${n?.fsPath}`),
        be.existsSync(a.fsPath) && (r = await M.workspace.fs.readDirectory(a));
      let c = { apps: [] },
        l = r.filter((d) => d[1] === M.FileType.Directory);
      return (c.apps = l), c;
    }
    async _getVEXaiImageVersionsLocal(t, e) {
      let o = require("os").homedir();
      console.log(o);
      let s = M.Uri.joinPath(
          M.Uri.file(o),
          `.${i.Extension.id}`,
          "vexai",
          t,
          "images"
        ),
        n = e || s,
        a = [];
      N._logHandler(`VEXOS Platform: ${t}`),
        N._logHandler(`VEXOS Search Location: ${s?.fsPath}`),
        be.existsSync(n.fsPath) && (a = await M.workspace.fs.readDirectory(n));
      let r = { latest: "", latest_priv: "", catalog: [], catalog_priv: [] },
        c = /ai3dimage_\d{8}_\d{1}.tar.gz/,
        l = /ai3dimage_\d{8}_\d{1}_priv.tar.gz/,
        d = /^ai3dimage_\d{8}_\d{1}$/,
        m = /^ai3dimage_\d{8}_\d{1}_priv$/,
        w = a.filter(
          (C) =>
            (c.test(C[0]) && C[1] === M.FileType.File) ||
            (d.test(C[0]) && C[1] === M.FileType.Directory)
        ),
        b = a.filter(
          (C) =>
            (l.test(C[0]) && C[1] === M.FileType.File) ||
            (m.test(C[0]) && C[1] === M.FileType.Directory)
        );
      return (
        w.forEach((C) => {
          r.catalog.push(Se.basename(C[0], ".zip "));
        }),
        b.forEach((C) => {
          r.catalog_priv.push(Se.basename(C[0], ".zip "));
        }),
        r.catalog.sort(N._sortVEXOSListCB),
        r.catalog_priv.sort(N._sortVEXOSListCB),
        (r.latest = r.catalog[0] ? r.catalog[0] : ""),
        (r.latest_priv = r.catalog_priv[0] ? r.catalog_priv[0] : ""),
        r
      );
    }
    static _sortVEXOSListCB(t, e) {
      var o = t.toUpperCase(),
        s = e.toUpperCase();
      let n = o.split("_"),
        a = s.split("_"),
        r = {
          major: Number(n[2]),
          minor: Number(n[3]),
          build: Number(n[4]),
          beta: Number(n[5]),
        },
        c = {
          major: Number(a[2]),
          minor: Number(a[3]),
          build: Number(a[4]),
          beta: Number(a[5]),
        };
      return r.major > c.major
        ? -1
        : r.major < c.major
        ? 1
        : r.minor > c.minor
        ? -1
        : r.minor < c.minor
        ? 1
        : r.build > c.build
        ? -1
        : r.build < c.build
        ? 1
        : r.beta > c.beta
        ? c.beta === 0
          ? 1
          : -1
        : r.beta < c.beta
        ? r.beta === 0
          ? -1
          : 1
        : 0;
    }
    static _sortSDKListCB(t, e) {
      var o = t.toUpperCase(),
        s = e.toUpperCase();
      let n = o.split("_"),
        a = s.split("_"),
        r = {
          major: Number(n[2]),
          minor: Number(n[3]),
          build: Number(n[4]),
          beta: Number(n[5]),
          rerelease: Number(n[6]) ? Number(n[6]) : void 0,
        },
        c = {
          major: Number(a[2]),
          minor: Number(a[3]),
          build: Number(a[4]),
          beta: Number(a[5]),
          rerelease: Number(n[6]) ? Number(n[6]) : void 0,
        };
      if (r.major > c.major) return -1;
      if (r.major < c.major) return 1;
      if (r.minor > c.minor) return -1;
      if (r.minor < c.minor) return 1;
      if (r.build > c.build) return -1;
      if (r.build < c.build) return 1;
      if (r.beta > c.beta) return c.beta === 0 ? 1 : -1;
      if (r.beta < c.beta) return r.beta === 0 ? -1 : 1;
      if (r.rerelease && c.rerelease) {
        if (r.beta > c.beta) return -1;
        if (r.beta < c.beta) return 1;
      } else {
        if (!r.rerelease && c.rerelease) return -1;
        if (r.rerelease && !c.rerelease) return 1;
      }
      return 0;
    }
    static async _unzipFile(t, e, o, s) {
      let n = e ? e.fsPath : Se.dirname(t.fsPath),
        a = M.Uri.joinPath(M.Uri.file(n), Se.basename(t.fsPath, ".zip ")),
        r = Se.basename(t.fsPath),
        c = !1,
        l = !1;
      console.log(`zip folder: ${a.fsPath}`),
        console.log(`File Uri DIR: ${Se.dirname(t.fsPath)}`),
        console.log(`PathToUnzip: ${Se.dirname(n)}`),
        N._logHandler(`Zip folder: ${a.fsPath}`),
        N._logHandler(`File Uri DIR: ${Se.dirname(t.fsPath)}`),
        N._logHandler(`File Uri BASE: ${Se.basename(t.fsPath)}`),
        N._logHandler(`PathToUnzip: ${Se.dirname(n)}`);
      let d = (f) => {
        console.log(f),
          o && (o.report({ message: f }), N._logHandler(`Unzip: ${f}`));
      };
      d(`${r}: Starting Unzip`);
      let m = be.statSync(t.fsPath),
        w = be.createReadStream(`${t.fsPath}`),
        b = Oo.Extract({ path: `${n}` });
      w.pipe(b).on("close", () => {
        console.log("Unzipper Close"), (c = !0);
      }),
        w.on("error", (f) => {
          d(`${r}: Error - ${f}`), (c = !0), (l = !0);
        }),
        b.on("error", (f) => {
          console.error(f);
        });
      let E = `${r}: Unziping File`,
        T = 0,
        O = 0;
      for (
        console.time("Unzip"), o.report({ message: "Unzip", increment: -100 });
        !w.destroyed;

      ) {
        await new Promise((z) => setTimeout(z, 50));
        let f = w.bytesRead,
          k = f - T;
        (T = f),
          (O += (k / m.size) * 100),
          o.report({
            increment: (k / m.size) * 100,
            message: `Unziping ${Se.basename(t.fsPath)}: ${O.toFixed(2)}%`,
          }),
          console.timeLog(
            "Unzip",
            `Diff %${O} ${w.bytesRead / 1024}kB/${m.size / 1024}kB`
          );
      }
      return (
        console.timeEnd("Unzip"),
        d(`${r}: Unzip Finished`),
        await new Promise((f) => setTimeout(f, 1e3)),
        l
      );
    }
    async _downloadHttpsFile(t, e, o, s, n = 500) {
      N._logHandler("Https Download Start");
      let a = M.Uri.joinPath(t, Se.basename(e));
      N._logHandler(`URL: ${e}`),
        N._logHandler(`Destination: ${a.fsPath}`),
        be.existsSync(t.fsPath) ||
          (console.log("Creating Directory", t),
          await M.workspace.fs.createDirectory(t));
      let r = be.createWriteStream(a.fsPath),
        c = 0,
        l = !1,
        d,
        m = new Date(),
        w = (S) => Number(new Date()) - Number(S),
        b = 0,
        C = {
          checkServerIdentity: (S, W) => this._checkServer(S, W),
          ALPNProtocols: ["HTTP / 1.1"],
        },
        E = new URL(e);
      console.log(E);
      let T = {
        timeout: 5e3,
        method: "GET",
        hostname: E.hostname,
        path: E.pathname,
        headers: {
          "User - Agent": `VEX VSC Extension/${i.Extension.version()}`,
        },
        agent: new Zt.Agent(C),
      };
      T.agent = new Zt.Agent(C);
      let O = 0,
        f = "",
        k = 0,
        z = Zt.request(T, function (S) {
          console.log(S),
            (k = N._bytesToMBytes(Number(S.headers["content - length"]))),
            S.on("data", (W) => {
              d = S.statusCode;
              let V = N._bytesToMBytes(W.length);
              c += V;
              let X = (c / k) * 100;
              (O = (V / W.length) * 100),
                (f = `Downloading ${Se.basename(e)}:(${c.toFixed(
                  1
                )}MB/${k.toFixed(1)}MB) ${X.toFixed(1)}%`);
              let ye = `Downloading ${Se.basename(e)}:(${c.toFixed(
                  2
                )}MB/${k.toFixed(2)}MB) ${X.toFixed(2)}%`,
                se = `Downloading ${Se.basename(e)}:(${c}MB/${k}MB) ${X.toFixed(
                  2
                )}%`;
              b.toFixed(0) !== X.toFixed(0) &&
                ((b = X), N._logHandler(`${se}`)),
                d === 200 && r.write(W);
            }),
            S.on("error", (W) => {
              console.log(`Error ${W}`),
                (l = !0),
                M.window.showErrorMessage("Download Failed"),
                N._logHandler(`Download Error: ${W}`);
            }),
            S.on("end", () => {
              console.log("Response Recieved"),
                (l = !0),
                this._showUiInfo &&
                  (M.window.showInformationMessage("Download Complete"),
                  N._logHandler("Download Complete"));
            });
        });
      z.on("error", (S) => {
        z.destroy(), S.errno === -3008 && (d = 408), console.log(d), (l = !0);
      }),
        z.on("timeout", () => {
          z.destroy();
        }),
        z.end(),
        s !== void 0 &&
          s.onCancellationRequested(() => {
            M.window.showErrorMessage("Download Canceled"),
              console.log("User canceled the long running operation"),
              (l = !0),
              M.window.showErrorMessage("Download Canceled"),
              z.destroy(),
              r.destroy(),
              be.rmSync(a.fsPath);
          });
      let Z = 0;
      for (; !l; )
        if ((await new Promise((S) => setTimeout(S, 250)), o)) {
          let S = c - Z;
          (Z = c), o.report({ increment: S / k, message: f });
        }
      return (
        N._logHandler(`Https Download Result:${d}: ${tt.get(d)}`), r.close(), d
      );
    }
    async _readHttpsFile(t, e, o) {
      N._logHandler("Https Read Start"), N._logHandler(`URL: ${t}`);
      let s = Buffer.alloc(0),
        n = 0,
        a = !1,
        r,
        c = new Date(),
        l = (E) => Number(new Date()) - Number(E),
        d = 0,
        m = {
          checkServerIdentity: (E, T) => this._checkServer(E, T),
          ALPNProtocols: ["HTTP / 1.1"],
        },
        w = new URL(t);
      console.log(w);
      let b = {
        timeout: 5e3,
        method: "GET",
        hostname: w.hostname,
        path: w.pathname,
        headers: {
          "User-Agent": `VEX VSC Extension/${i.Extension.version()}`,
        },
      };
      b.agent = new Zt.Agent(m);
      let C = Zt.request(b, function (E) {
        console.log(E);
        let T = N._bytesToMBytes(Number(E.headers["content-length"]));
        E.on("data", (O) => {
          r = E.statusCode;
          let f = N._bytesToMBytes(O.length);
          n += f;
          let k = (n / T) * 100;
          e !== void 0 &&
            e.report({
              increment: (f / T) * 100,
              message: `Downloading ${Se.basename(t)}:(${n.toFixed(
                1
              )}MB/${T.toFixed(1)}MB) ${k.toFixed(1)}%`,
            });
          let z = `Downloading ${Se.basename(t)}:(${n.toFixed(2)}MB/${T.toFixed(
              2
            )}MB) ${k.toFixed(2)}%`,
            Z = `Downloading ${Se.basename(t)}:(${n}MB/${T}MB) ${k.toFixed(
              2
            )}%`;
          d.toFixed(0) !== k.toFixed(0) && ((d = k), N._logHandler(`${Z}`)),
            r === 200 && (s = Buffer.concat([s, O], s.length + O.length));
        }),
          E.on("error", (O) => {
            console.log(`Error ${O}`),
              (a = !0),
              M.window.showErrorMessage("Download Failed"),
              N._logHandler(`Download Error: ${O}`);
          }),
          E.on("end", () => {
            console.log("Response Recieved"),
              (a = !0),
              this._showUiInfo &&
                (M.window.showInformationMessage("Download Complete"),
                N._logHandler("Download Complete"));
          });
      });
      for (
        C.on("error", (E) => {
          C.destroy(), E.errno === -3008 && (r = 408), console.log(r), (a = !0);
        }),
          C.on("timeout", () => {
            C.destroy();
          }),
          C.end(),
          o !== void 0 &&
            o.onCancellationRequested(() => {
              M.window.showErrorMessage("Download Canceled"),
                console.log("User canceled the long running operation"),
                (a = !0),
                M.window.showErrorMessage("Download Canceled"),
                C.destroy();
            });
        !a;

      )
        await new Promise((E) => setTimeout(E, 100));
      return (
        N._logHandler(`Https Download Result:${r}: ${tt.get(r)}`),
        {
          httpsCode: r,
          buf: s,
        }
      );
    }
    _checkServer(t, e) {
      let o = ci.checkServerIdentity(t, e);
      if (o) return o;
      let s = "d3CXX9n6T51t+sgda2XjSPrpP0K6iCkzxv29gL18TYE=";
      if ((console.log(sha256(e.pubkey)), sha256(e.pubkey) !== s)) {
        let r = `Certificate verification error: The public key of '${e.subject.CN}' does not match our pinned fingerprint`;
        return new Error(r);
      }
      let n =
        "F6:F3:F4:67:89:7A:F6:1F:FD:BC:23:D6:9F:DA:9D:B7:8C:95:63:E8:89:EC:C4:E9:69:78:C6:22:91:38:AC:84";
      if (e.fingerprint256 !== n) {
        let r = `Certificate verification error: The certificate of '${e.subject.CN}' does not match our pinned fingerprint`;
        return new Error(r);
      }
      let a;
      do
        console.log("Subject Common Name:", e.subject.CN),
          console.log("  Certificate SHA256 fingerprint:", e.fingerprint256),
          console.log("  Public key ping-sha256:", sha256(e.pubkey)),
          (a = e.fingerprint256),
          (e = e.issuerCertificate);
      while (e.fingerprint256 !== a);
    }
    On(t, e) {
      switch (t) {
        case "Log":
          N._logCB = e;
          break;
      }
    }
    static _logHandler(t) {
      let e = `${N._classType} ${t}`;
      N._logCB && N._logCB(e);
    }
    static _bytesToMBytes(t) {
      return typeof t == "number"
        ? t
          ? t / 1024 / 1024
          : 0
        : t instanceof Buffer && t.length
        ? t.length / 1024 / 1024
        : 0;
    }
  },
  Xt = N;
Xt._classType = "Resource Manager: ";
((e) => {
  let _;
  ((l) => (
    (l.v5 = "V5"),
    (l.exp = "EXP"),
    (l.iq2 = "IQ2"),
    (l.vscode = "vscode"),
    (l.ai2d = "2d"),
    (l.ai3d = "3d")
  ))((_ = e.ContentFolders || (e.ContentFolders = {})));
  let t;
  ((n) => ((n.sdk = "sdk"), (n.stubs = "stubs")))(
    (t = e.ManifestType || (e.ManifestType = {}))
  );
})(Xt || (Xt = {}));
var Ee = L(require("vscode"));
var li = L(require("path")),
  Tt = class {
    constructor(t) {
      (this._deviceListButton = Ee.window.createStatusBarItem(
        Ee.StatusBarAlignment.Left,
        6
      )),
        (this._deviceListButton.command = Tt.listDevicesCmdId),
        (this._deviceListButton.text = ""),
        (this._deviceListButton.tooltip = "List VEX Devices"),
        (this._selectSlotButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          5
        )),
        (this._selectSlotButton.command = Tt.slotCmdId),
        (this._selectSlotButton.text = "$(vex-slot) Slot 1"),
        (this._selectSlotButton.tooltip = "Select Slot"),
        (this._buildButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          4
        )),
        (this._buildButton.command = Tt.buildCmdId),
        (this._buildButton.text = "$(vex-build)"),
        (this._buildButton.tooltip = "Build Project"),
        (this._playButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          3
        )),
        (this._playButton.command = Tt.playCmdId),
        (this._playButton.text = "$(vex-play)"),
        (this._playButton.tooltip = "Play User Program"),
        (this._stopButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          2
        )),
        (this._stopButton.command = Tt.stopCmdId),
        (this._stopButton.text = "$(vex-stop)"),
        (this._stopButton.tooltip = "Stop User Program"),
        (this._selectProjectButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          1
        )),
        (this._selectProjectButton.command = Tt.selectProjectCmdId),
        (this._selectProjectButton.text = "No Project Selected"),
        (this._selectProjectButton.tooltip = "Select Active Project"),
        (this._pythonFileButton = Ee.window.createStatusBarItem(
          Ee.StatusBarAlignment.Left,
          0
        )),
        (this._pythonFileButton.command = Tt.selectPythonCmdId),
        (this._pythonFileButton.text = ".py"),
        (this._pythonFileButton.tooltip = "Select Python File");
    }
    async selectSlot() {
      let t = "Select Slot",
        e = [
          "$(vex-slot) Slot 1",
          "$(vex-slot) Slot 2",
          "$(vex-slot) Slot 3",
          "$(vex-slot) Slot 4",
          "$(vex-slot) Slot 5",
          "$(vex-slot) Slot 6",
          "$(vex-slot) Slot 7",
          "$(vex-slot) Slot 8",
        ],
        o = await Ee.window.showQuickPick(e, {
          placeHolder: t,
          onDidSelectItem: () => {},
        }),
        s = 1;
      return (
        o
          ? (s = Number(o.split(" ")[2]))
          : (s = Number(this._selectSlotButton.text.split(" ")[2])),
        (this._selectSlotButton.text = `$(vex-slot) Slot ${s}`),
        s
      );
    }
    async selectProject(t) {
      let e = "Select Project",
        o = [],
        s = 1,
        n;
      t.searchForProjectsInWorkspace(),
        t.projectList.forEach((r) => {
          r.updateProjectSettings(),
            r.projectUri.fsPath === t.selectedProject.projectUri.fsPath
              ? (n = r)
              : o.push({
                  label: r.name,
                  description: r.language,
                  detail: r.projectUri.fsPath,
                }),
            s++;
        }),
        o.unshift({
          label: `$(star-full)${n.name}`,
          description: n.language,
          detail: n.projectUri.fsPath,
        }),
        Ee.window.showInputBox();
      let a = await Ee.window.showQuickPick(o, {
        placeHolder: e,
        onDidSelectItem: () => {},
        canPickMany: !1,
      });
      if (!!a)
        return t.projectList.filter((r) => r.projectUri.fsPath === a.detail)[0];
    }
    async pickPythonFile(t) {
      let e = "Select Python File",
        o = [],
        s = 1;
      t.selectedProject.updateProjectSettings();
      let n = new Ee.RelativePattern(t.selectedProject.projectUri, "**/*.py"),
        a = new Ee.RelativePattern(t.selectedProject.projectUri, "**/build/**");
      (await Ee.workspace.findFiles(n, a)).forEach((c) => {
        let l = {
          description: Ee.workspace.asRelativePath(c, !1),
          label: `$(python-qp)${li.basename(c.fsPath)}`,
        };
        o.push(l);
      });
      let r = await Ee.window.showQuickPick(o, {
        placeHolder: e,
        onDidSelectItem: () => {},
        canPickMany: !1,
      });
      if (!!r) return r;
    }
    get buildBtn() {
      return this._buildButton;
    }
    get playBtn() {
      return this._playButton;
    }
    get stopBtn() {
      return this._stopButton;
    }
    get deviceListBtn() {
      return this._deviceListButton;
    }
    get selectSlotBtn() {
      return this._selectSlotButton;
    }
    get selectProjectBtn() {
      return this._selectProjectButton;
    }
    get selectPythonFileBtn() {
      return this._pythonFileButton;
    }
  },
  Me = Tt;
(Me.playCmdId = `${i.Extension.id}.statusbar.play`),
  (Me.stopCmdId = `${i.Extension.id}.statusbar.stop`),
  (Me.buildCmdId = `${i.Extension.id}.statusbar.build`),
  (Me.listDevicesCmdId = `${i.Extension.id}.statusbar.listDevices`),
  (Me.slotCmdId = `${i.Extension.id}.statusbar.pickSlot`),
  (Me.selectProjectCmdId = `${i.Extension.id}.statusbar.pickProject`),
  (Me.selectPythonCmdId = `${i.Extension.id}.statusbar.pickPythonFile`);
var pt = L(require("fs")),
  Bo = L(require("os")),
  xt = L(require("vscode"));
var ee;
((a) => {
  function _(c, l) {}
  a.splitTerminal = _;
  let t;
  ((O) => (
    (O.black = "\x1B[30m"),
    (O.red = "\x1B[31m"),
    (O.green = "\x1B[32m"),
    (O.yellow = "\x1B[33m"),
    (O.blue = "\x1B[34m"),
    (O.magenta = "\x1B[35m"),
    (O.cyan = "\x1B[36m"),
    (O.white = "\x1B[37m"),
    (O.reset = "\x1B[0m")
  ))((t = a.TextColors || (a.TextColors = {})));
  let e;
  ((f) => (
    (f.arrowUp = "\x1B[A"),
    (f.arrowDown = "\x1B[B"),
    (f.arrowRight = "\x1B[C"),
    (f.arrowLeft = "\x1B[D"),
    (f.insert = "\x1B[@"),
    (f.delete = "\x1B[P"),
    (f.clearScreen = "'\x1B[2J\x1B[3J\x1B[;H'"),
    (f.clearLineToEnd = "\x1B[0K"),
    (f.clearLineToStart = "\x1B[1K"),
    (f.clearLineEntire = "\x1B[2K")
  ))((e = a.AnsiEscapeCodes || (a.AnsiEscapeCodes = {})));

  function o(c, l) {
    return `${l}${c}${"\x1B[0m"}`;
  }
  a.colorText = o;
  class s {
    constructor(l, d) {
      (this._name = l || "Interactive Terminal"),
        (this._line = []),
        (this._writeEmitter = new xt.EventEmitter()),
        (this._position = 0),
        (this._cmdIndex = 0),
        (this._previousCmds = []),
        (this._recieveInputDataCB = this.defaultTerminalInputHandler);
      let m = {
          onDidWrite: this._writeEmitter.event,
          open: () => {},
          close: () => {},
          handleInput: (b) => {
            this._recieveInputDataCB(this, b);
          },
        },
        w = xt.Uri.joinPath(
          i.Extension.context.extensionUri,
          "resources",
          "icons",
          "vex.svg"
        );
      if (d) {
        let b = {
          parentTerminal: d,
        };
        this._terminal = xt.window.createTerminal({
          name: l,
          location: b,
          pty: m,
          iconPath: w,
        });
      } else
        this._terminal = xt.window.createTerminal({
          name: l,
          pty: m,
          iconPath: w,
        });
    }
    write(l, d) {
      let m = "";
      l instanceof Uint8Array
        ? l.forEach((b) => {
            m += String.fromCharCode(b);
          })
        : (m = l);
      let w = d ? a.colorText(m, d) : m;
      this._writeEmitter.fire(w);
    }
    writeLine(l, d) {
      this.write(
        l +
          `\r
`,
        d
      );
    }
    clear() {
      this._writeEmitter.fire("\x1B[2J\x1B[3J\x1B[;H");
    }
    registerCB(l, d) {
      switch (l) {
        case "Input":
          this._onDataRecievedCB = d;
          break;
      }
    }
    defaultTerminalInputHandler(l, d) {
      this._onDataRecievedCB && this._onDataRecievedCB(d);
    }
    get terminal() {
      return this._terminal;
    }
  }
  a.Interactive = s;
  let r = class {
      static setBuildLogFileHome(l) {
        pt.existsSync(l.fsPath) || pt.mkdirSync(l.fsPath),
          l && (r._LogHomeUri = xt.Uri.joinPath(l, r._LogFile));
      }
      static writeToTempLog(l) {
        !r._LogHomeUri ||
          pt.appendFileSync(r._LogHomeUri.fsPath, l, {
            encoding: "utf-8",
          });
      }
      static read() {
        return !r._LogHomeUri || !pt.existsSync(r._LogHomeUri.fsPath)
          ? ""
          : pt.readFileSync(r._LogHomeUri.fsPath, {
              encoding: "utf-8",
            });
      }
      static clearTempLog() {
        !r._LogHomeUri ||
          (pt.existsSync(r._LogHomeUri.fsPath) &&
            pt.rmSync(r._LogHomeUri.fsPath, {
              force: !0,
            }));
      }
      constructor(l) {
        (this._regexError = new RegExp(/(error:|Error \d)/)),
          (this._regexWarning = new RegExp(/(warning:|Warning \d)/)),
          (this._regexCodeLineOrCaret = new RegExp(
            /(\^|\;|\)\;|\w;|\w\(|\w\[|\]\;)/
          )),
          (this._regexWarningErrorText = new RegExp(
            /\d\s(warning|warnings|error|errors)\s/
          )),
          (this._writeEmitter = new xt.EventEmitter()),
          (this._msg = "");
        let d = "",
          m = {
            onDidWrite: this._writeEmitter.event,
            open: () =>
              this._writeEmitter.fire(`Log\r
`),
            close: () => {},
            handleInput: (C) => {
              if (C === "\r") {
                d.includes("clear") || d.includes("cls")
                  ? this.clear()
                  : this.write(`\r
`),
                  (d = "");
                return;
              }
              if (C === "\x7F") {
                if (d.length === 0) return;
                (d = d.substr(0, d.length - 1)),
                  this._writeEmitter.fire("\x1B[D"),
                  this._writeEmitter.fire("\x1B[P");
                return;
              }
              (d += C), this.write(C);
            },
          },
          w = {
            parentTerminal: l,
          },
          b = xt.Uri.joinPath(
            i.Extension.context.extensionUri,
            "resources",
            "icons",
            "vex.svg"
          );
        this._terminal = xt.window.createTerminal({
          name: "Log",
          location: w,
          pty: m,
          iconPath: b,
        });
      }
      write(l, d) {
        if (typeof l == "string") {
          let m = d ? a.colorText(l, d) : l;
          r.writeToTempLog(m), this._writeEmitter.fire(m);
          return;
        } else if (typeof l != "string") {
          let m = d ? a.colorText(l.toString(), d) : l.toString();
          r.writeToTempLog(m), this._writeEmitter.fire(m);
          return;
        }
      }
      writeLogText(l, d) {
        let m = d ? a.colorText(l, d) : l;
        this._writeEmitter.fire(l);
      }
      writeBuildText(l) {
        if (l instanceof Uint8Array) {
          this.parseBuildText(l, "\x1B[37m", !1);
          return;
        }
      }
      writeBuildErrorText(l) {
        if (l instanceof Uint8Array) {
          this.parseBuildText(l, "\x1B[31m", !0);
          return;
        }
      }
      clear() {
        a.Log.clearTempLog(), this._writeEmitter.fire("\x1B[2J\x1B[3J\x1B[;H");
      }
      parseBuildText(l, d, m = !1) {
        let w = [],
          b = "",
          C = !1;
        if (
          (l.forEach((f) => {
            (b += f.toString(16) + " "),
              Bo.type() === "Linux" &&
                (f === 10
                  ? ((this._msg += String.fromCharCode(13)),
                    (this._msg += String.fromCharCode(f)),
                    w.push(this._msg),
                    (this._previousChar = 0),
                    (this._msg = ""),
                    (C = !0),
                    (b = ""))
                  : (this._msg += String.fromCharCode(f))),
              Bo.type() === "Darwin" &&
                (f === 10
                  ? ((this._msg += String.fromCharCode(13)),
                    (this._msg += String.fromCharCode(f)),
                    w.push(this._msg),
                    (this._previousChar = 0),
                    (this._msg = ""),
                    (C = !0),
                    (b = ""))
                  : (this._msg += String.fromCharCode(f))),
              Bo.type() === "Windows_NT" &&
                (f === 13
                  ? ((this._msg += String.fromCharCode(f)),
                    (this._previousChar = f))
                  : this._previousChar !== 13 && f === 10
                  ? ((this._msg += String.fromCharCode(f)),
                    (this._msg += String.fromCharCode(13)),
                    w.push(this._msg),
                    (this._previousChar = 0),
                    (this._msg = ""),
                    (C = !0))
                  : this._previousChar === 13 && f === 10
                  ? ((this._msg += String.fromCharCode(f)),
                    w.push(this._msg),
                    (this._previousChar = 0),
                    (this._msg = ""),
                    (C = !0))
                  : (this._msg += String.fromCharCode(f)));
          }),
          !C || w.length === 0)
        )
          return;
        if (!m) {
          w.forEach((f) => this.write(f, d));
          return;
        }
        let E = this._previousTextColor ? this._previousTextColor : d,
          T = "",
          O = !1;
        w.forEach((f) => {
          this._regexWarning.test(f)
            ? ((E = "\x1B[33m"),
              (T += f),
              (this._previousTextColor = "\x1B[33m"))
            : this._regexError.test(f)
            ? ((E = "\x1B[31m"),
              (T += f),
              (this._previousTextColor = "\x1B[31m"))
            : this._regexCodeLineOrCaret.test(f)
            ? (T += o(`${f}`, E))
            : this._regexWarningErrorText.test(f)
            ? ((T += o(`${f}`, "\x1B[36m")),
              (T += `\r
`),
              (O = !0))
            : (T += f);
        }),
          (this._previousTextColor = E),
          this.write(T, E),
          O ? (this._previousTextColor = d) : (this._previousTextColor = E);
      }
      get terminal() {
        return this._terminal;
      }
    },
    n = r;
  (n._LogFile = "tempBuildLog.txt"), (a.Log = n);
})(ee || (ee = {}));
var us = L(require("ws"));
var $e = class {
    constructor(t, e) {
      this._deviceURL = `${i.Extension.id}/device`;
      this._vscodeURL = `${i.Extension.id}/vscode-command`;
      this._websocketServer = void 0;
      this._websocketDeviceList = [];
      this._websocketVSCodeCommand = [];
      this._wssConfig = {};
      this._isRunning = !1;
      this._DEFAULT_PORT = 7071;
      this._DEFAULT_HOST = "0.0.0.0";
      this._PORT_MIN = 1;
      this._PORT_MAX = 65535;
      (this._wssConfig = t || {
        port: this._DEFAULT_PORT,
        host: this._DEFAULT_HOST,
      }),
        this.on("Log", e),
        $e._logHandler("VEX Websocket Server Initialized");
    }
    start(t) {
      this._isRunning ||
        ((this._isRunning = !0),
        (this._wssConfig = t || this._wssConfig),
        $e._logHandler(
          `Starting Websocket Server on Host:${this._wssConfig.host} Port:${this._wssConfig.port}`
        ),
        this._setupWebsocketServer());
    }
    stop() {
      !this._isRunning ||
        (this._websocketDeviceList.forEach((t) => {
          t[0].close(
            $e.ExitCode.CLOSE_GOING_AWAY,
            "Vex websocket server closing, server disabled"
          );
        }),
        (this._websocketDeviceList = []),
        this._websocketVSCodeCommand.forEach((t) => {
          t[0].close(
            $e.ExitCode.CLOSE_GOING_AWAY,
            "Vex websocket server closing, server disabled"
          );
        }),
        (this._websocketVSCodeCommand = []),
        $e._logHandler(
          `Stoping Websocket Server on Host:${this._wssConfig.host} Port:${this._wssConfig.port}`
        ),
        this._websocketServer.close());
    }
    _setupWebsocketServer() {
      let t = this.validateServerConfig(this._wssConfig);
      if (t !== $e.ValidateErrorCodes.VALID_CONFIG) {
        (this._isRunning = !0), $e._logHandler(`Invalid Server Config: ${t}`);
        return;
      }
      this.websocketServer && this._websocketServer.removeAllListeners(),
        (this._websocketServer = new us.Server(this._wssConfig)),
        this._websocketServer.on("error", (e) => this._eventWSSError(e)),
        this._websocketServer.on("close", () => this._eventWSSClose()),
        this._websocketServer.on("connection", (e, o) =>
          this._eventWSSConnection(e, o)
        );
    }
    _eventWSSConnection(t, e) {
      let o = this.uuidv4(),
        s = Math.floor(Math.random() * 360),
        n = {
          id: o,
          color: s,
        };
      console.log(o, s),
        console.log(t),
        console.log(e),
        e.url.includes(this._deviceURL)
          ? (console.log(e.socket.remoteAddress),
            console.log(e.socket.localAddress),
            this._websocketDeviceList.push([t, e, o]))
          : e.url.includes(this._vscodeURL)
          ? this._websocketVSCodeCommand.push([t, e, o])
          : t.close(
              $e.ExitCode.CLOSE_PROTOCOL_ERROR,
              `Vex websocket server error, URL: ${e.url}, not accepted.
  Try "ws://${e.socket.localAddress}:${e.socket.localPort}/${this._deviceURL}
" to access user port stream and try ""ws://${e.socket.localAddress}:${e.socket.localPort}/${this._vscodeURL}"`
            ),
        t.on("close", () => {
          this._websocketDeviceList.pop();
        }),
        t.on("", () => {}),
        this._onConnectionHandler(t, e);
    }
    _eventWSSError(t) {
      $e._logHandler(`Error: ${t}`), (this._isRunning = !1);
    }
    _eventWSSClose() {
      this._isRunning = !1;
    }
    uuidv4() {
      return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(
        /[xy]/g,
        function (t) {
          var e = (Math.random() * 16) | 0,
            o = t === "x" ? e : (e & 3) | 8;
          return o.toString(16);
        }
      );
    }
    updateServerConfig(t) {
      this._websocketDeviceList.forEach((e) => {
        e[0].close(
          $e.ExitCode.SERVICE_RESTART,
          "Vex websocket server restarting, server settings changed"
        );
      }),
        this.vscodeWSList.forEach((e) => {
          e[0].close(
            $e.ExitCode.SERVICE_RESTART,
            "Vex websocket server restarting, server settings changed"
          );
        }),
        this._websocketServer.close(),
        (this._websocketServer = new us.Server(t));
    }
    validateServerConfig(t) {
      if (t.port <= this._PORT_MIN && t.port >= this._PORT_MAX)
        return $e.ValidateErrorCodes.INVALID_PORT;
      let e = /.*\..*\..*\..*/,
        o = /[0-255]\.[0-255]\.[0-255]\.[0-255]/,
        s = /.*\:.*\:.*\:.*\:.*\:.*\:.*\:.*/,
        n =
          /[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}\:[0-9a-fA-F]{4}/,
        a = /[A-Za-z\-]*/;
      if (e.test(t.host)) {
        if ((console.log(o.test(t.host)), !o.test(t.host)))
          return $e.ValidateErrorCodes.INVALID_IPV4;
      } else if (s.test(t.host)) {
        if (!n.test(t.host)) return $e.ValidateErrorCodes.INVALID_IPV6;
      } else if (!a.test(t.host)) return $e.ValidateErrorCodes.INVALID_HOSTNAME;
      return $e.ValidateErrorCodes.VALID_CONFIG;
    }
    get websocketServer() {
      return this._websocketServer;
    }
    get deviceWSList() {
      return this._websocketDeviceList;
    }
    get vscodeWSList() {
      return this._websocketVSCodeCommand;
    }
    get deviceURL() {
      return this._deviceURL;
    }
    get vscodeURL() {
      return this._vscodeURL;
    }
    get host() {
      return this._wssConfig.host;
    }
    get port() {
      return this._wssConfig.port;
    }
    on(t, e) {
      switch (t) {
        case "Log":
          $e._logCB = e;
          break;
        case "connection":
          this._connectionCB = e;
          break;
      }
    }
    static _logHandler(t) {
      let e = `${$e._classType} ${t}`;
      console.log(e), $e._logCB && $e._logCB(e);
    }
    _onConnectionHandler(t, e) {
      this._connectionCB && this._connectionCB(t, e);
    }
  },
  Ht = $e;
Ht._classType = "VEX Websocket Server: ";
((e) => {
  let _;
  ((k) => (
    (k[(k.CLOSE_NORMAL = 1e3)] = "CLOSE_NORMAL"),
    (k[(k.CLOSE_GOING_AWAY = 1001)] = "CLOSE_GOING_AWAY"),
    (k[(k.CLOSE_PROTOCOL_ERROR = 1002)] = "CLOSE_PROTOCOL_ERROR"),
    (k[(k.CLOSE_UNSUPPORTED = 1003)] = "CLOSE_UNSUPPORTED"),
    (k[(k.RESERVED = 1004)] = "RESERVED"),
    (k[(k.CLOSED_NO_STATUS = 1005)] = "CLOSED_NO_STATUS"),
    (k[(k.CLOSE_ABNORMAL = 1006)] = "CLOSE_ABNORMAL"),
    (k[(k.UNSUPPORTED_PAYLOAD = 1007)] = "UNSUPPORTED_PAYLOAD"),
    (k[(k.POLICY_V = 1008)] = "POLICY_V"),
    (k[(k.CLOSE_TOO_LARGE = 1009)] = "CLOSE_TOO_LARGE"),
    (k[(k.MANDATORY_EXTENSION = 1010)] = "MANDATORY_EXTENSION"),
    (k[(k.SERVER = 1011)] = "SERVER"),
    (k[(k.SERVICE_RESTART = 1012)] = "SERVICE_RESTART"),
    (k[(k.TRY_AGAIN_LATER = 1013)] = "TRY_AGAIN_LATER"),
    (k[(k.BAD_GATEWAY = 1014)] = "BAD_GATEWAY"),
    (k[(k.TLS_HANDSHAKE_FAIL = 1015)] = "TLS_HANDSHAKE_FAIL")
  ))((_ = e.ExitCode || (e.ExitCode = {})));
  let t;
  ((c) => (
    (c[(c.VALID_CONFIG = 0)] = "VALID_CONFIG"),
    (c[(c.INVALID_PORT = -1)] = "INVALID_PORT"),
    (c[(c.INVALID_IPV4 = -2)] = "INVALID_IPV4"),
    (c[(c.INVALID_IPV6 = -3)] = "INVALID_IPV6"),
    (c[(c.INVALID_HOSTNAME = -4)] = "INVALID_HOSTNAME")
  ))((t = e.ValidateErrorCodes || (e.ValidateErrorCodes = {})));
})(Ht || (Ht = {}));
var Fo;
((t) => {
  function _(e) {
    let o = new qe(e, "VEX Resource Manager", "vex.resourceManager.debuglog"),
      s = (a) => o.appendLine(`${a}`),
      n = new Xt(e, s);
    e.subscriptions.push(
      st.commands.registerCommand(
        i.Extension.ResourceManager.downloadToolchainID,
        async (a) => {
          let r = {
            command: i.Extension.ResourceManager.downloadToolchainID,
            details: "",
            statusCode: 0,
            json: "",
          };
          return await n.downloadToolChain(a);
        }
      )
    ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.downloadSDKID,
          async (a, r, c, l) => {
            console.log(a, c);
            let d = {
              command: i.Extension.ResourceManager.downloadSDKID,
              details: "",
              statusCode: 0,
              json: "",
            };
            return (
              (d.statusCode = await n.downloadSDK(a, r, c, l)),
              (d.details = ""),
              (d.json = ""),
              console.log("Response Base", d),
              d
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getSDKVersionID,
          async (a, r, c) => {
            let l = {
                command: i.Extension.ResourceManager.getSDKVersionID,
                details: "",
                statusCode: 0,
                json: "",
              },
              d = await n.getSDKVersions(a, r, c);
            return (
              console.log("Response Base", d),
              (l.json = JSON.stringify(d)),
              console.log("Response Base", l),
              l
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.downloadVexosID,
          async (a, r) => {
            let c = await n.downloadVEXosFile(a, r);
            return {
              command: i.Extension.ResourceManager.downloadVexosID,
              details: "",
              statusCode: c,
              json: "",
            };
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getVexosVersionID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.getVexosVersionID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = await n.getVEXosVersions(a, r);
            return (
              console.log("Response Base", l),
              (c.json = JSON.stringify(l)),
              console.log("Response Base", c),
              c
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getVexosManifestID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.getVexosManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = await n.getLatestVEXosManifest(a, r);
            return (
              console.log("Response Base", l),
              (c.json = JSON.stringify(l)),
              console.log("Response Base", c),
              c
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getVexaiAppListManifestID,
          async (a) => {
            let r = {
                command: i.Extension.ResourceManager.getVexaiAppListManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              c = await n.getVEX3DaiAppListVersions(a);
            return (
              console.log("Response Base", c),
              (r.json = JSON.stringify(c)),
              console.log("Response Base", r),
              r
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getVexaiAppManifestID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.getVexaiAppManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = await n.getVEXaiAppManifest(a, r);
            return (
              console.log("Response Base", l),
              (c.json = JSON.stringify(l)),
              console.log("Response Base", c),
              c
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.downloadVexaiAppID,
          async (a, r) => {
            let c = await n.downloadVEXaiApp(a, r);
            return {
              command: i.Extension.ResourceManager.downloadVexaiAppID,
              details: "",
              statusCode: c,
              json: "",
            };
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.getVexaiImageManifestID,
          async (a) => {
            let r = {
                command: i.Extension.ResourceManager.getVexaiImageManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              c = await n.getVEXaiImageVersions(a);
            return (
              console.log("Response Base", c),
              (r.json = JSON.stringify(c)),
              console.log("Response Base", r),
              r
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.downloadVexaiID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.getVexosManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = await n.downloadVEXaiImage(r, a);
            return (
              console.log("Response Base", l),
              (c.json = JSON.stringify(l)),
              console.log("Response Base", c),
              c
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.verifyVexaiImageID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.getVexosManifestID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = new Map([
                [0, "Success"],
                [-1, "File does not exist"],
                [-2, "Not a file"],
                [-3, "Manifest does not exist"],
              ]),
              d = await n.verifyVEXaiImage(r, a);
            return (
              console.log("Response Base", d),
              (c.statusCode = d.errorCode),
              (c.details = l.get(d.errorCode)
                ? l.get(d.errorCode)
                : `Unknown Code (${d.errorCode})`),
              (c.json = JSON.stringify(d)),
              console.log("Response Base", c),
              c
            );
          }
        )
      ),
      e.subscriptions.push(
        st.commands.registerCommand(
          i.Extension.ResourceManager.downloadDriverInstallerID,
          async (a, r) => {
            let c = {
                command: i.Extension.ResourceManager.downloadDriverInstallerID,
                details: "",
                statusCode: 0,
                json: "",
              },
              l = await n.downloadDriverInstaller(a, r);
            return (
              console.log("Response Base", l),
              console.log("Response Base", c),
              (c.statusCode = l),
              c
            );
          }
        )
      );
  }
  t.setup = _;
})(Fo || (Fo = {}));
var p = L(require("vscode"));
var g = L(require("vscode")),
  Po = L(require("path"));
var jt = L(require("os"));
var Xo = class {
  constructor(t) {
    this._onDidChangeTreeData = new g.EventEmitter();
    this.onDidChangeTreeData = this._onDidChangeTreeData.event;
    this._systemInfo = [];
    this._deviceInfo = {};
    this._getDeviceType = (t, e) => {
      if (e === i.Platform.V5)
        switch (t) {
          case 2:
            return "Motor";
          case 3:
            return "LED";
          case 4:
            return "Rotation";
          case 5:
            return "Motor";
          case 6:
            return "Inertial";
          case 7:
            return "Distance";
          case 8:
            return "Radio";
          case 9:
            return "Controller";
          case 10:
            return "Brain";
          case 11:
            return "Vision";
          case 12:
            return "3wire";
          case 13:
            return "Partner";
          case 14:
            return "Battery";
          case 15:
            return "Solenoid";
          case 16:
            return "Optical";
          case 17:
            return "Magnet";
          case 22:
            return "Radio - Internal";
          case 26:
            return "3D AI Camera";
          case -127:
            return "Generic";
          default:
            return t.toString();
        }
      else if (e === i.Platform.EXP)
        switch (t) {
          case 2:
            return "Motor";
          case 3:
            return "LED";
          case 4:
            return "Rotation";
          case 5:
            return "Motor";
          case 6:
            return "Inertial";
          case 7:
            return "Distance";
          case 8:
            return "Radio";
          case 9:
            return "Controller";
          case 10:
            return "Brain";
          case 11:
            return "Vision";
          case 12:
            return "3wire";
          case 13:
            return "Partner";
          case 14:
            return "Battery";
          case 15:
            return "Solenoid";
          case 16:
            return "Optical";
          case 17:
            return "Magnet";
          case 22:
            return "Radio - Internal";
          case 26:
            return "3D AI Camera";
          case -127:
            return "Generic";
          default:
            return t.toString();
        }
      else if (e === i.Platform.IQ2)
        switch (t) {
          case 2:
            return "Motor";
          case 3:
            return "Touchled";
          case 4:
            return "Color";
          case 5:
            return "Bumper";
          case 6:
            return "Gyro";
          case 7:
            return "Sonar";
          case 8:
            return "Radio";
          case 11:
            return "Vision";
          case 16:
            return "Optical";
          case 19:
            return "Distance";
          case -127:
            return "Generic";
          default:
            return t.toString();
        }
    };
    (this.context = t),
      (this._cautionIcon = new g.ThemeIcon(
        "warning",
        new g.ThemeColor("list.warningForeground")
      )),
      (this._errorIcon = new g.ThemeIcon(
        "error",
        new g.ThemeColor("list.errorForeground")
      ));
  }
  async getSystemInfo() {
    let t = [],
      e = await this.pickSystemToParse(this._device);
    if ((e && t.push(e), !this._externalDeviceList[0])) return t;
    let o = this._externalDeviceList?.length;
    return (
      await new Promise(async (n, a) => {
        let r = 0;
        for (
          this._externalDeviceList.forEach(async (c) => {
            let l = await this.pickSystemToParse(c);
            l && t.push(l), r++;
          });
          r !== o;

        )
          await i.Utils.asyncSleep(500);
        n(0);
      }),
      t
    );
  }
  async pickSystemToParse(t) {
    if (t instanceof J) {
      let e = this._parseAppParentNode(t);
      if (t instanceof Ct) return (e.items = this._parseV5Brain(t)), e;
      if (t instanceof Je) return (e.items = this._parseV5Controller(t)), e;
      if (t instanceof ft)
        return t.bootMode === I.BootMode.app
          ? ((e.items = this._parseIQ2Brain(t)), e)
          : ((t.bootMode === I.BootMode.rom || t.bootMode === I.BootMode.ram) &&
              (e.items = this._parseBootloaderIQ2Brain(t)),
            e);
      if (t instanceof We) return (e.items = this._parseIQ2Controller(t)), e;
      if (t instanceof vt)
        return (
          t.bootMode === I.BootMode.app && (e.items = this._parseEXPBrain(t)),
          (t.bootMode === I.BootMode.rom || t.bootMode === I.BootMode.ram) &&
            (e.items = this._parseBootloaderEXPBrain(t)),
          e
        );
      if (t instanceof et) return (e.items = this._parseEXPController(t)), e;
      if (t instanceof _e) return e;
    } else if (t instanceof Be) {
      let e = this._parseDFUParentNode(t);
      if (t instanceof Ot || t instanceof Lt)
        return (e.items = this._parseBootloaderBrain(t)), e;
      if (t instanceof Et || t instanceof St)
        return (e.items = this._parseBootloaderController(t)), e;
    } else if (t instanceof ro) {
      let e = this._parseAIAppParentNode(t);
      if (t instanceof _e) return (e.items = this._parseAI3DCamera(t)), e;
    } else if (t instanceof no) {
      let e = this._parseAIDFUParentNode(t);
      if (t instanceof Bt) return (e.items = this._parseDFUAI3DCamera(t)), e;
    } else return;
  }
  _parseAIAppParentNode(t) {
    let e = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      o = !1,
      s = !1,
      n = t.bootMode === I.BootMode.app ? `( ${t.name} )` : `( ${t.bootMode} )`;
    if (!(t instanceof _e)) return e;
    (o = t?.ssidChanged ? !0 : o),
      (o = t?.passwordChanged ? !0 : o),
      (o = t?.needsUpdate ? !0 : o),
      (o = t?.updateList.length ? !0 : o),
      (o = t?.isVexupdateMissing ? !0 : o),
      t.ssidChanged || t.passwordChanged
        ? (n =
            t.bootMode === I.BootMode.app
              ? `( ${t.name} ) - reboot needed`
              : `( ${t.bootMode} ) - reboot needed`)
        : t.isVexupdateMissing && !t.isAlive
        ? (n = " ( vexupdate app is missing)")
        : t.isAlive
        ? t.systemInfo
          ? (n =
              t.bootMode === I.BootMode.app
                ? `( ${t.name} )`
                : `( ${t.bootMode} )`)
          : (n = `( ${t.bootMode} )`)
        : (n = "initializing . . .");
    let a = e.type;
    return (
      t.json === "" || t.isVexupdateMissing || !t.isAlive
        ? (a = g.TreeItemCollapsibleState.None)
        : (a = g.TreeItemCollapsibleState.Expanded),
      s
        ? (e = {
            icon: new g.ThemeIcon(
              "device-camera",
              new g.ThemeColor("list.errorForeground")
            ),
            name: `${t.platform} ${t.device} ${n}`,
            type: a,
            tag: `${t.platform} ${t.device}`,
            items: [],
          })
        : o
        ? (e = {
            icon: new g.ThemeIcon(
              "device-camera",
              new g.ThemeColor("list.warningForeground")
            ),
            name: `${t.platform} ${t.device} ${n}`,
            type: a,
            tag: `${t.platform} ${t.device}`,
            items: [],
          })
        : (e = {
            icon: new g.ThemeIcon(
              "device-camera",
              new g.ThemeColor("charts.green")
            ),
            name: `${t.platform} ${t.device} ${n}`,
            type: a,
            tag: `${t.platform} ${t.device}`,
            items: [],
          }),
      e
    );
  }
  _parseAppParentNode(t) {
    let e = !1,
      o = !1,
      s =
        t.bootMode === I.BootMode.app
          ? `( ${t.robotName} )`
          : `( ${t.bootMode} )`;
    t.device === i.Device.Brain
      ? (s =
          t.bootMode === I.BootMode.app
            ? `( ${t.robotName} )`
            : `( ${t.bootMode} )`)
      : t.device === i.Device.Controller
      ? ((s =
          t.bootMode === I.BootMode.app
            ? `( ${t.robotName} )`
            : `( ${t.bootMode} )`),
        (s = s === "(  )" ? "" : s))
      : (s =
          t.bootMode === I.BootMode.app
            ? `( ${t.robotName} )`
            : `( ${t.bootMode} )`),
      (t.needsVexosUpdate && t.bootMode === I.BootMode.app) ||
      (t.device === i.Device.Brain &&
        (t.bootMode === I.BootMode.rom || t.bootMode === I.BootMode.ram))
        ? (e = !0)
        : ((t.device === i.Device.Controller &&
            t.bootMode === I.BootMode.rom) ||
            t.bootMode === I.BootMode.dfu) &&
          (o = !0);
    let n = t.platform === "IQ2" ? "IQ 2nd Generation" : t.platform,
      a = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    return (
      o
        ? (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("list.errorForeground")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          })
        : e
        ? (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("list.warningForeground")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          })
        : (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("charts.green")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          }),
      a
    );
  }
  _parseAIDFUParentNode(t) {
    let e =
      t.bootMode === I.BootMode.app ? `( ${t.name} )` : `( ${t.bootMode} )`;
    e = t.bootMode === I.BootMode.app ? `( ${t.name} )` : `( ${t.bootMode} )`;
    let o = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      s = g.TreeItemCollapsibleState.Expanded;
    return (
      (o = {
        icon: new g.ThemeIcon(
          "device-camera",
          new g.ThemeColor("list.warningForeground")
        ),
        name: `${t.platform} ${t.device} ${e}`,
        type: s,
        tag: `${t.platform} ${t.device}`,
        items: [],
      }),
      o
    );
  }
  _parseDFUParentNode(t) {
    let e = !1,
      o = !1,
      s = `( ${t.bootMode} )`;
    t.bootMode === I.BootMode.dfu && (o = !0);
    let n = t.platform === "IQ2" ? "IQ 2nd Generation" : t.platform,
      a = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.Expanded,
      };
    return (
      o
        ? (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("list.errorForeground")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          })
        : e
        ? (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("list.warningForeground")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          })
        : (a = {
            icon: new g.ThemeIcon(
              `vex-${t.platform}-${t.device}`,
              new g.ThemeColor("charts.green")
            ),
            name: `${n} ${t.device} ${s}`,
            type: g.TreeItemCollapsibleState.Expanded,
            tag: `${n} ${t.device} ${t.bootMode}`,
            items: [],
          }),
      a
    );
  }
  _parseV5Brain(t) {
    this._systemInfo = [];
    let e = 0,
      o = 1,
      s = 2,
      n = 3;
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      c = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    if (a?.brain?.name) {
      t.needsVexosUpdate
        ? (r = {
            icon: this.getVEXThemeIcon(
              t.platform,
              t.device,
              "list.warningForeground"
            ),
            name: " Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos-update",
            items: [],
          })
        : (r = {
            icon: this.getVEXThemeIcon(t.platform, t.device, ""),
            name: " Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            items: [],
          });
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[e].items;
      t.needsVexosUpdate
        ? d.push({
            icon: this._cautionIcon,
            name: "VEXos	 : " + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "",
            items: [],
          })
        : d.push({
            name: "VEXos	 : " + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "vexos-good",
            items: [],
          }),
        d.push({
          name: "name	 : " + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team	 : " + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id		 : " + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python	 : " +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              " (" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[o].items = this._getSerialNode(t)),
        (l[s].items = this._getProgramsTree(a)),
        (l[n].items = this._getDeviceNode(a, t.platform));
    }
    return (
      a?.system?.radio_linked
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: " Controller - linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : a?.system?.controller_tethered
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: " Controller - tethered",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: " Controller - not linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          }),
      [r, c]
    );
  }
  _parseV5Controller(t) {
    this._systemInfo = [];
    let e = 0,
      o = 1,
      s = 2,
      n = 3;
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      c = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    if (a?.brain?.name) {
      t.needsVexosUpdate
        ? (r = {
            icon: this.getVEXThemeIcon(
              t.platform,
              i.Device.Brain,
              "list.warningForeground"
            ),
            name: " Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos-update",
            items: [],
          })
        : (r = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Brain, ""),
            name: " Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            items: [],
          });
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[e].items;
      t.needsVexosUpdate
        ? d.push({
            icon: this._cautionIcon,
            name: "VEXos	 : " + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "",
            items: [],
          })
        : d.push({
            name: "VEXos	 : " + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "vexos-good",
            items: [],
          }),
        d.push({
          name: "name	 : " + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team	 : " + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id		 : " + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python	 : " +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              " (" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[o].items = this._getSerialNode(t)),
        (l[s].items = this._getProgramsTree(a)),
        (l[n].items = this._getDeviceNode(a, t.platform));
    } else
      r = {
        icon: this.getVEXThemeIcon(
          t.platform,
          i.Device.Brain,
          "list.warningForeground"
        ),
        name: " Brain - not linked",
        type: g.TreeItemCollapsibleState.None,
        items: [],
      };
    if (
      a?.controller &&
      (this._device instanceof We || this._device instanceof Je)
    ) {
      c = {
        icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
        name: " Controller",
        type: g.TreeItemCollapsibleState.Expanded,
        tag: "controller",
        items: [],
      };
      let l = c.items;
      l.push({
        name: "radio		: " + i.Utils.vexos.toVersion(a.controller.radio),
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
        l.push({
          name: "usb			: " + i.Utils.vexos.toVersion(a.controller.version),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        });
    }
    return [r, c];
  }
  _parseBootloaderIQ2Brain(t) {
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      c = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    if (a?.brain?.bootloader) {
      r = {
        icon: this.getVEXThemeIcon(
          t.platform,
          t.device,
          "list.warningForeground"
        ),
        name: " Brain",
        type: g.TreeItemCollapsibleState.Expanded,
        tag: "vexos - update",
        items: [],
      };
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      d.push({
        icon: this._cautionIcon,
        name: "VEXos: 0.0 .0 .0",
        type: g.TreeItemCollapsibleState.None,
        tag: "vexos - update",
        items: [],
      }),
        d.push({
          name: "bootloader:" + a.brain.bootloader,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        d.push({
          name: "version:" + i.Utils.vexos.toVersion(a.brain.version),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        (d = l[1].items),
        d.push({
          name: "communication:" + t.communication,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        });
      let m = jt.type() === "Windows_NT" ? "user:" : "user:";
      d.push({
        name: m + t.user,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      });
    }
    return [r];
  }
  _parseIQ2Brain(t) {
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = { items: [], name: "", type: g.TreeItemCollapsibleState.None },
      c = { items: [], name: "", type: g.TreeItemCollapsibleState.None };
    if (a?.brain?.name) {
      t.needsVexosUpdate
        ? (r = {
            icon: this.getVEXThemeIcon(
              t.platform,
              t.device,
              "list.warningForeground"
            ),
            name: "Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos - update",
            items: [],
          })
        : (r = {
            icon: this.getVEXThemeIcon(t.platform, t.device, ""),
            name: "Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "brain",
            items: [],
          });
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      t.needsVexosUpdate
        ? d.push({
            icon: this._cautionIcon,
            name: "VEXos:" + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "",
            items: [],
          })
        : d.push({
            name: "VEXos:" + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "vexos - good",
            items: [],
          }),
        d.push({
          name: "name:" + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team:" + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id:" + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python:" +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              "(" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[1].items = this._getSerialNode(t)),
        (l[2].items = this._getProgramsTree(a)),
        (l[3].items = this._getDeviceNode(a, t.platform));
    }
    return (
      a?.system?.radio_linked
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : a?.system?.controller_tethered
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - tethered",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - not linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          }),
      [r, c]
    );
  }
  _parseIQ2Controller(t) {
    let a = t.vexComSystemInfo,
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      c = { items: [], name: "", type: g.TreeItemCollapsibleState.None };
    if (a?.brain?.name) {
      r = {
        icon: this.getVEXThemeIcon(t.platform, t.device, ""),
        name: "Brain",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      };
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      d.push({
        name: "VEXos:" + i.Utils.vexos.toVersion(a.brain.vexos),
        type: g.TreeItemCollapsibleState.None,
        tag: "vexos - good",
        items: [],
      }),
        d.push({
          name: "name:" + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team:" + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id:" + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python:" +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              "(" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[1].items = this._getSerialNode(t)),
        (l[2].items = this._getProgramsTree(a)),
        (l[3].items = this._getDeviceNode(a, t.platform));
    } else
      r = {
        icon: this.getVEXThemeIcon(
          t.platform,
          i.Device.Brain,
          "list.warningForeground"
        ),
        name: "Brain - not linked",
        type: g.TreeItemCollapsibleState.None,
        items: [],
      };
    if (a?.controller) {
      t.needsRadioUpdate || t.needsUsbUpdate
        ? (c = {
            icon: this.getVEXThemeIcon(
              t.platform,
              i.Device.Controller,
              "list.warningForeground "
            ),
            name: "Controller",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos - controller - update",
            items: [],
          })
        : (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "controller",
            items: [],
          });
      let l = c.items;
      t.needsRadioUpdate
        ? l.push({
            icon: this._cautionIcon,
            name: "radio:" + i.Utils.vexos.toVersion(a.controller.version),
            type: g.TreeItemCollapsibleState.None,
            tag: "controller - radio",
            items: [],
          })
        : l.push({
            name: "radio:" + i.Utils.vexos.toVersion(a.controller.version),
            type: g.TreeItemCollapsibleState.None,
            tag: "controller - radio",
            items: [],
          }),
        t.needsUsbUpdate
          ? l.push({
              icon: this._cautionIcon,
              name: "usb:" + i.Utils.vexos.toVersion(a.controller.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller - atmel",
              items: [],
            })
          : l.push({
              name: "usb:" + i.Utils.vexos.toVersion(a.controller.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller - atmel",
              items: [],
            });
    } else if (a?.controller_boot) {
      c = {
        icon: this.getVEXThemeIcon(
          t.platform,
          i.Device.Controller,
          "list.errorForeground"
        ),
        name: "Controller",
        type: g.TreeItemCollapsibleState.Expanded,
        tag: "vexos - controller - update",
        items: [],
      };
      let l = c.items;
      l.push({
        icon: this._errorIcon,
        name: "radio: 0.0 .0 .0",
        type: g.TreeItemCollapsibleState.None,
        tag: "controller - radio",
        items: [],
      }),
        t.needsUsbUpdate
          ? l.push({
              icon: this._cautionIcon,
              name: "usb:" + i.Utils.vexos.toVersion(a.controller_boot.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller - atmel",
              items: [],
            })
          : l.push({
              name: "usb:" + i.Utils.vexos.toVersion(a.controller_boot.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller - atmel",
              items: [],
            });
    }
    return [r, c];
  }
  _parseEXPBrain(t) {
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = { items: [], name: "", type: g.TreeItemCollapsibleState.None },
      c = { items: [], name: "", type: g.TreeItemCollapsibleState.None };
    if (a?.brain?.name) {
      t.needsVexosUpdate
        ? (r = {
            icon: this.getVEXThemeIcon(
              t.platform,
              t.device,
              "list.warningForeground"
            ),
            name: "Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos - update",
            items: [],
          })
        : (r = {
            icon: this.getVEXThemeIcon(t.platform, t.device, ""),
            name: "Brain",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "brain",
            items: [],
          });
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      t.needsVexosUpdate
        ? d.push({
            icon: this._cautionIcon,
            name: "VEXos:" + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "",
            items: [],
          })
        : d.push({
            name: "VEXos:" + i.Utils.vexos.toVersion(a.brain.vexos),
            type: g.TreeItemCollapsibleState.None,
            tag: "vexos - good",
            items: [],
          }),
        d.push({
          name: "name:" + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team:" + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id:" + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python:" +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              "(" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[1].items = this._getSerialNode(t)),
        (l[2].items = this._getProgramsTree(a)),
        (l[3].items = this._getDeviceNode(a, t.platform));
    }
    return (
      a?.system?.radio_linked
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : a?.system?.controller_tethered
        ? (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - tethered",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: "Controller - not linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          }),
      [r, c]
    );
  }
  _parseBootloaderEXPBrain(t) {
    if (t.json === "{}" || t.json === "") return;
    let a = t.vexComSystemInfo,
      r = { items: [], name: "", type: g.TreeItemCollapsibleState.None },
      c = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    if (a?.brain?.bootloader) {
      r = {
        icon: this.getVEXThemeIcon(
          t.platform,
          t.device,
          "list.warningForeground"
        ),
        name: "Brain",
        type: g.TreeItemCollapsibleState.Expanded,
        tag: "vexos - update",
        items: [],
      };
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      d.push({
        icon: this._cautionIcon,
        name: "VEXos: 0.0 .0 .0",
        type: g.TreeItemCollapsibleState.None,
        tag: "vexos - update",
        items: [],
      }),
        d.push({
          name: "bootloader:" + a.brain.bootloader,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        d.push({
          name: "version:" + i.Utils.vexos.toVersion(a.brain.version),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        (d = l[1].items),
        d.push({
          name: "communication:" + t.communication,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        });
      let m = jt.type() === "Windows_NT" ? "user:" : "user:";
      d.push({
        name: m + t.user,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      });
    }
    return [r];
  }
  _parseEXPController(t) {
    let a = t.vexComSystemInfo,
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      c = { items: [], name: "", type: g.TreeItemCollapsibleState.None };
    if (a?.brain?.name) {
      r = {
        icon: this.getVEXThemeIcon(t.platform, i.Device.Brain, ""),
        name: "Brain",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      };
      let l = r.items;
      l.push({
        name: "system",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        l.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "programs",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        l.push({
          name: "devices",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[0].items;
      d.push({
        name: "VEXos	 : " + i.Utils.vexos.toVersion(a.brain.vexos),
        type: g.TreeItemCollapsibleState.None,
        tag: "vexos-good",
        items: [],
      }),
        d.push({
          name: "name	 : " + a.brain.name,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "name",
        }),
        d.push({
          name: "team	 : " + a.brain.team,
          type: g.TreeItemCollapsibleState.None,
          items: [],
          tag: "team",
        }),
        d.push({
          name: "id		 : " + a.brain.ssn.substring(2),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.vms &&
          a.vms.count > 0 &&
          d.push({
            name:
              "python	 : " +
              i.Utils.vexos.toVersion(a.vms.items[0].version) +
              " (" +
              a.vms.items[0].crc32 +
              ")",
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: 0,
          }),
        (l[1].items = this._getSerialNode(t)),
        (l[2].items = this._getProgramsTree(a)),
        (l[3].items = this._getDeviceNode(a, t.platform));
    } else
      a?.system?.controller_tethered
        ? (r = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Brain, ""),
            name: " Brain - tethered",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          })
        : (r = {
            icon: this.getVEXThemeIcon(
              t.platform,
              i.Device.Brain,
              "list.warningForeground"
            ),
            name: " Brain - not linked",
            type: g.TreeItemCollapsibleState.None,
            items: [],
          });
    if (a?.controller) {
      t.needsRadioUpdate || t.needsUsbUpdate
        ? (c = {
            icon: this.getVEXThemeIcon(
              t.platform,
              i.Device.Controller,
              "list.warningForeground"
            ),
            name: " Controller",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "vexos-controller-update",
            items: [],
          })
        : (c = {
            icon: this.getVEXThemeIcon(t.platform, i.Device.Controller, ""),
            name: " Controller",
            type: g.TreeItemCollapsibleState.Expanded,
            tag: "controller",
            items: [],
          });
      let l = c.items;
      t.needsRadioUpdate
        ? l.push({
            icon: this._cautionIcon,
            name: "radio		: " + i.Utils.vexos.toVersion(a.controller.version),
            type: g.TreeItemCollapsibleState.None,
            tag: "controller-radio",
            items: [],
          })
        : l.push({
            name: "radio		: " + i.Utils.vexos.toVersion(a.controller.version),
            type: g.TreeItemCollapsibleState.None,
            tag: "controller-radio",
            items: [],
          }),
        t.needsUsbUpdate
          ? l.push({
              icon: this._cautionIcon,
              name: "usb			: " + i.Utils.vexos.toVersion(a.controller.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller-atmel",
              items: [],
            })
          : l.push({
              name: "usb			: " + i.Utils.vexos.toVersion(a.controller.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller-atmel",
              items: [],
            });
    } else if (a?.controller_boot) {
      c = {
        icon: this.getVEXThemeIcon(
          t.platform,
          i.Device.Controller,
          "list.errorForeground"
        ),
        name: " Controller",
        type: g.TreeItemCollapsibleState.Expanded,
        tag: "vexos-controller-update",
        items: [],
      };
      let l = c.items;
      l.push({
        icon: this._errorIcon,
        name: "radio		: 0.0.0.0",
        type: g.TreeItemCollapsibleState.None,
        tag: "controller-radio",
        items: [],
      }),
        t.needsUsbUpdate
          ? l.push({
              icon: this._cautionIcon,
              name: "usb			: " + i.Utils.vexos.toVersion(a.controller_boot.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller-atmel",
              items: [],
            })
          : l.push({
              name: "usb			: " + i.Utils.vexos.toVersion(a.controller_boot.atmel),
              type: g.TreeItemCollapsibleState.None,
              tag: "controller-atmel",
              items: [],
            });
    }
    return [r, c];
  }
  _parseDFUEXPBrain(t) {}
  _parseAI3DCamera(t) {
    if (t.json === "{}" || t.json === "") return;
    let n = t.systemInfo,
      a = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      },
      r = {
        items: [],
        name: "",
        type: g.TreeItemCollapsibleState.None,
      };
    if (n?.device?.name) {
      let c = a.items;
      c.push({
        name: "device",
        type: g.TreeItemCollapsibleState.Expanded,
        items: [],
      }),
        c.push({
          name: "serial port",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        }),
        c.push({
          name: "apps",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let l = c[0].items;
      l.push({
        name: "id			 : " + n?.device?.id,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
        t.needsUpdate
          ? l.push({
              icon: this._cautionIcon,
              name: "version		 : " + n?.device?.version,
              type: g.TreeItemCollapsibleState.None,
              tag: "3D-AI-Update-Image",
              items: [],
            })
          : l.push({
              name: "version		 : " + n?.device?.version,
              type: g.TreeItemCollapsibleState.None,
              items: [],
            }),
        l.push({
          name: "access point",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let d = l[2].items;
      t.ssidChanged
        ? d.push({
            icon: this._cautionIcon,
            name: "ssid		 : " + n?.device?.name + " - reboot needed ",
            type: g.TreeItemCollapsibleState.None,
            tag: "",
            items: [],
          })
        : d.push({
            name: "ssid			 : " + n?.device?.name,
            type: g.TreeItemCollapsibleState.None,
            items: [],
            tag: "3d-ssid",
          }),
        t.passwordChanged
          ? d.push({
              icon: this._cautionIcon,
              name: "password		 :: ****** - reboot needed ",
              type: g.TreeItemCollapsibleState.None,
              tag: "",
              items: [],
            })
          : d.push({
              name: "password		 : ******",
              type: g.TreeItemCollapsibleState.None,
              items: [],
              tag: "3d-password",
            });
      let w = jt.networkInterfaces()["Wi-Fi"],
        b = !1;
      console.log(w);
      let C;
      w?.forEach((O) => {
        O.family === "IPv4" && (C = O);
      }),
        w &&
          C &&
          n?.device?.access_point.client_macs.forEach((O) => {
            if (C.mac === O) {
              b = !0;
              return;
            }
          }),
        d.push({
          name: `connected	 : ${b}`,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        d.push({
          name: "mac address",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
      let E = d[3].items,
        T = n?.device?.access_point?.host_mac
          ? n?.device?.access_point?.host_mac
          : "";
      if (
        (E.push({
          name: "host	: " + T,
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        n?.device?.access_point.client_macs)
      ) {
        E.push({
          name: "clients",
          type: g.TreeItemCollapsibleState.Expanded,
          items: [],
        });
        let O = E[1].items;
        (n?.device?.access_point.client_macs).length &&
          n?.device?.access_point.client_macs.forEach((f) => {
            w
              ? C.mac === f
                ? O.push({
                    name: `${f}	 : ( ${jt.hostname} ) `,
                    type: g.TreeItemCollapsibleState.None,
                    items: [],
                  })
                : O.push({
                    name: f,
                    type: g.TreeItemCollapsibleState.None,
                    items: [],
                  })
              : O.push({
                  name: f,
                  type: g.TreeItemCollapsibleState.None,
                  items: [],
                });
          });
      } else
        E.push({
          name: "clients",
          type: g.TreeItemCollapsibleState.None,
          items: [],
        });
      (c[1].items = this._getAISerialNode(t)),
        (c[2].items = this._getAIAppsTree(n, t));
    }
    return a.items;
  }
  _parseDFUAI3DCamera(t) {
    let a = {
      items: [],
      name: "",
      type: g.TreeItemCollapsibleState.None,
    };
    a = {
      name: "device",
      type: g.TreeItemCollapsibleState.Expanded,
      items: [],
    };
    let r = a.items;
    return (
      r.push({
        icon: this._cautionIcon,
        name: "version		 :",
        type: g.TreeItemCollapsibleState.None,
        tag: "3D-AI-Update-Image",
        items: [],
      }),
      r.push({
        name: "bootloader	 : " + t.bootMode,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      r.push({
        name: "vid			 : 0x" + t.vid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      r.push({
        name: "pid			 : 0x" + t.pid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      [a]
    );
  }
  _parseBootloaderBrain(t) {
    let a = {
      items: [],
      name: "",
      type: g.TreeItemCollapsibleState.None,
    };
    t.bootMode === I.BootMode.dfu
      ? (a = {
          icon: this.getVEXThemeIcon(
            t.platform,
            t.device,
            "list.errorForeground"
          ),
          name: ` ${t.device}`,
          type: g.TreeItemCollapsibleState.Expanded,
          tag: "dfu-recover",
          items: [],
        })
      : (a = {
          icon: this.getVEXThemeIcon(
            t.platform,
            t.device,
            "list.errorForeground"
          ),
          name: ` ${t.device}`,
          type: g.TreeItemCollapsibleState.Expanded,
          tag: "vexos-update",
          items: [],
        });
    let r = a.items;
    r.push({
      name: "system",
      type: g.TreeItemCollapsibleState.Expanded,
      items: [],
    });
    let c = r[0].items;
    return (
      t.bootMode === I.BootMode.dfu
        ? c.push({
            icon: this._errorIcon,
            name: "VEXos		 : 0.0.0.0 ",
            type: g.TreeItemCollapsibleState.None,
            tag: "recover",
            items: [],
          })
        : c.push({
            icon: this._errorIcon,
            name: "VEXos		 : 0.0.0.0 ",
            type: g.TreeItemCollapsibleState.None,
            tag: "vexos-update",
            items: [],
          }),
      c.push({
        name: "bootloader	 : " + t.bootMode,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      c.push({
        name: "vid			 : 0x" + t.vid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      c.push({
        name: "pid			 : 0x" + t.pid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      [a]
    );
  }
  _parseBootloaderController(t) {
    let a = {
      items: [],
      name: "",
      type: g.TreeItemCollapsibleState.None,
    };
    a = {
      icon: this.getVEXThemeIcon(t.platform, t.device, "list.errorForeground"),
      name: ` ${t.device}`,
      type: g.TreeItemCollapsibleState.Expanded,
      tag: "dfu-recover",
      items: [],
    };
    let r = a.items;
    r.push({
      name: "system",
      type: g.TreeItemCollapsibleState.Expanded,
      items: [],
    });
    let c = r[0].items;
    c.push({
      icon: this._errorIcon,
      name: "radio		 : 0.0.0.0 ",
      type: g.TreeItemCollapsibleState.None,
      tag:
        t.bootMode === I.BootMode.dfu
          ? `controller-radio-${t.bootMode}`
          : "controller-radio",
      items: [],
    }),
      c.push({
        icon: this._errorIcon,
        name: "usb			 : 0.0.0.0 ",
        type: g.TreeItemCollapsibleState.None,
        tag: "controller-atmel",
        items: [],
      });
    let l = {
      name: "bootloader	 : " + t.bootMode,
      type: g.TreeItemCollapsibleState.Expanded,
      items: [],
    };
    return (
      l.items.push({
        name: "vid	 : 0x" + t.vid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      l.items.push({
        name: "pid	 : 0x" + t.pid,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      c.push(l),
      [a]
    );
  }
  _getSerialNode(t) {
    let e = [];
    e.push({
      name: "communication	 : " + t.communication,
      type: g.TreeItemCollapsibleState.None,
      items: [],
    });
    let o = jt.type() === "Windows_NT" ? "user				 : " : "user			 : ";
    return (
      e.push({
        name: o + t.user,
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
      e
    );
  }
  _getAISerialNode(t) {
    let e = [];
    e.push({
      name: "admin	 : " + t.communication,
      type: g.TreeItemCollapsibleState.None,
      items: [],
    });
    let o = jt.type() === "Windows_NT" ? "terminal	 : " : "terminal : ";
    return (
      e.push({
        name: o + t.user,
        type: g.TreeItemCollapsibleState.None,
        items: [],
        tag: "3D-AI-Reset-Terminal",
      }),
      e
    );
  }
  _getProgramsTree(t) {
    let e = [];
    return (
      t.programs.items.forEach((o) => {
        if (o) {
          let s = Number(o.slot) + 1,
            n = Po.join("vex", s.toString()),
            a = "C++",
            r = Po.join(n, o.file + ".cpp");
          o.type === "bina" &&
            ((a = "Python"), (r = Po.join(n, o.file + ".py")));
          let c = {
            icon: g.ThemeIcon.File,
            name: `${s}:	 ${o.file}`,
            type: g.TreeItemCollapsibleState.Collapsed,
            items: [],
            data: s,
            tag: "program",
            slot: s,
            uri: r,
          };
          c.items.push({
            name: "slot		: " + s,
            type: g.TreeItemCollapsibleState.None,
            items: [],
            data: s,
          }),
            c.items.push({
              name: "file		: " + o.binfile,
              type: g.TreeItemCollapsibleState.None,
              items: [],
              data: o.binfile,
              tag: "binfile",
            }),
            c.items.push({
              name: "type		: " + a,
              type: g.TreeItemCollapsibleState.None,
              items: [],
              data: a,
            }),
            c.items.push({
              name: `size		: ${(o.size / 1024).toFixed(2)}kB`,
              type: g.TreeItemCollapsibleState.None,
              items: [],
              data: o.size,
            }),
            c.items.push({
              name: "time		: " + o.time,
              type: g.TreeItemCollapsibleState.None,
              items: [],
              data: o.time,
            }),
            e.push(c);
        }
      }),
      e.sort((o, s) => {
        let n = o.slot,
          a = s.slot;
        return n < a ? -1 : n > a ? 1 : 0;
      }),
      e
    );
  }
  _getDeviceNode(t, e) {
    let o = [],
      s = 23;
    for (let n = 0; n < t.devices.count; n++) {
      if (t.devices.items[n].type === 22 && e === i.Platform.EXP) continue;
      t.devices.items[n].port !== s
        ? o.push({
            name:
              "port_" +
              t.devices.items[n].port +
              "	 (" +
              this._getDeviceType(t.devices.items[n].type, e) +
              ")",
            type: g.TreeItemCollapsibleState.Collapsed,
            items: [],
          })
        : o.push({
            name: "Battery",
            type: g.TreeItemCollapsibleState.Collapsed,
            items: [],
          });
      let a = o[n].items;
      a.push({
        name: "type		 : " + this._getDeviceType(t.devices.items[n].type, e),
        type: g.TreeItemCollapsibleState.None,
        items: [],
      }),
        a.push({
          name:
            "version	 : " + i.Utils.vexos.toVersion(t.devices.items[n].version),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        a.push({
          name: "boot	 : " + i.Utils.vexos.toVersion(t.devices.items[n].boot),
          type: g.TreeItemCollapsibleState.None,
          items: [],
        });
    }
    return o;
  }
  _getAIAppsTree(t, e) {
    let o = [];
    return (
      t.apps.forEach((s) => {
        let n = !1,
          a = !1,
          r = !1;
        s.Status !== "install ok installed" &&
          ((n = !0),
          s.Status === "App Missing"
            ? (a = !0)
            : s.Status.includes("not-installed") && (r = !0));
        let c = n,
          l = !1;
        e?.updateList?.includes(s.Package) && (l = !0);
        let d = l;
        if (s) {
          let m = Po.join(`${s.Package}_${s.Version}_${s.Architecture}.deb`),
            w;
          c
            ? (w = {
                icon: this._errorIcon,
                name: `${s.Package}`,
                type: g.TreeItemCollapsibleState.Collapsed,
                items: [],
                uri: m,
                tag: "3D-AI-App-Update",
                appMissing: a,
              })
            : d
            ? (w = {
                icon: this._cautionIcon,
                name: `${s.Package}`,
                type: g.TreeItemCollapsibleState.Collapsed,
                items: [],
                uri: m,
                tag: "3D-AI-App-Update",
              })
            : (w = {
                icon: g.ThemeIcon.File,
                name: `${s.Package}`,
                type: g.TreeItemCollapsibleState.Collapsed,
                items: [],
                uri: m,
              }),
            w.items.push({
              name: `package			: ${s.Package}`,
              type: g.TreeItemCollapsibleState.None,
              items: [],
            }),
            !a &&
              !r &&
              (l
                ? w.items.push({
                    icon: this._cautionIcon,
                    name: "version		  : " + s.Version,
                    type: g.TreeItemCollapsibleState.None,
                    items: [],
                    tag: "3D-AI-App-Update",
                  })
                : w.items.push({
                    name: "version			: " + s.Version,
                    type: g.TreeItemCollapsibleState.None,
                    items: [],
                  }),
              w.items.push({
                name: "description		: " + s.Description,
                type: g.TreeItemCollapsibleState.None,
                items: [],
              }),
              w.items.push({
                name: "maintainer		: " + s.Maintainer,
                type: g.TreeItemCollapsibleState.None,
                items: [],
              })),
            n
              ? w.items.push({
                  icon: this._errorIcon,
                  name: "status		  : " + s.Status,
                  type: g.TreeItemCollapsibleState.None,
                  items: [],
                  tag: "3D-AI-App-Update",
                })
              : w.items.push({
                  name: "status			: " + s.Status,
                  type: g.TreeItemCollapsibleState.None,
                  items: [],
                }),
            o.push(w);
        }
      }),
      o
    );
  }
  getVEXThemeIcon(t, e, o) {
    let s = i.Extension.Icons.getIconStr(t, e);
    return new g.ThemeIcon(s, new g.ThemeColor(o));
  }
  refresh(t, e) {
    (this._device = t),
      (this._externalDeviceList = e),
      this.getSystemInfo()
        .then((o) => {
          (this._systemInfo = o), this._onDidChangeTreeData.fire(void 0);
        })
        .catch((o) => {
          console.log(o);
        });
  }
  clear(t) {
    this._systemInfo.length,
      (this._systemInfo = []),
      this._onDidChangeTreeData.fire(void 0);
  }
  clearSD() {
    (this._device = void 0),
      this.refresh(this._device, this._externalDeviceList);
  }
  clearAISD() {
    (this._externalDeviceList = []),
      this.refresh(this._device, this._externalDeviceList);
  }
  getTreeItem(t) {
    var e;
    if (t === void 0)
      e = new g.TreeItem("No systemInfo", g.TreeItemCollapsibleState.None);
    else {
      if (t.name === void 0) return;
      (e = new g.TreeItem(t.name, t.type)),
        t.icon !== void 0 && (e.iconPath = t.icon),
        t.tag !== void 0 &&
          (t.tag === "program" && (e.contextValue = "progItem"),
          t.tag === "EXP Brain app" && (e.contextValue = "expBrainItem"),
          (t.tag === "EXP Brain rom" ||
            t.tag === "EXP Brain ram" ||
            t.tag === "EXP Brain dfu") &&
            (e.contextValue = "expBrainItemBoot"),
          t.tag === "IQ 2nd Generation Brain app" &&
            (e.contextValue = "iq2BrainItem"),
          (t.tag === "IQ 2nd Generation Brain rom" ||
            t.tag === "IQ 2nd Generation Brain ram" ||
            t.tag === "IQ 2nd Generation Brain dfu") &&
            (e.contextValue = "iq2BrainItemBoot"),
          t.tag === "V5 Brain app" && (e.contextValue = "v5BrainItem"),
          t.tag === "EXP Controller app" &&
            (e.contextValue = "expControllerItem"),
          (t.tag === "EXP Controller rom" ||
            t.tag === "EXP Controller ram" ||
            t.tag === "EXP Controller dfu") &&
            (e.contextValue = "expControllerItemBoot"),
          t.tag === "IQ 2nd Generation Controller app" &&
            (e.contextValue = "iq2ControllerItem"),
          (t.tag === "IQ 2nd Generation Controller rom" ||
            t.tag === "IQ 2nd Generation Controller ram" ||
            t.tag === "IQ 2nd Generation Controller dfu") &&
            (e.contextValue = "iq2ControllerItemBoot"),
          t.tag.includes("V5 Controller") &&
            (e.contextValue = "v5ControllerItem"),
          t.tag === "program-empty" && (e.contextValue = "progEmptyItem"),
          t.tag === "binfile" && (e.contextValue = "fileItem"),
          t.tag === "slot" && (e.contextValue = "slotItem"),
          t.tag === "name" && (e.contextValue = "brainNameItem"),
          t.tag === "team" && (e.contextValue = "teamNumberItem"),
          t.tag === "vexos-update" && (e.contextValue = "vexosUpdateItem"),
          t.tag === "dfu-recover" && (e.contextValue = "dfuRecoverItem"),
          t.tag === "vexos-controller-update" &&
            (e.contextValue = "vexosControllerUpdateItem"),
          t.tag === "vexos-brain-update" &&
            (e.contextValue = "vexosBrainUpdateItem"),
          t.tag === "vexos-good" && (e.contextValue = "vexosGoodItem"),
          t.tag === "controller-atmel" &&
            (e.contextValue = "controllerAtmelItem"),
          t.tag === "controller-radio" &&
            (e.contextValue = "controllerRadioItem"),
          t.tag === "controller" && (e.contextValue = "controllerItem"),
          t.tag === "brain" && (e.contextValue = "brainItem")),
        t.uri !== void 0 && (e.resourceUri = g.Uri.file(t.uri)),
        t.data !== void 0 &&
          t.name.match("python") &&
          t.tag === "vmrefresh" &&
          (e.contextValue = "python");
    }
    return e;
  }
  getChildren(t) {
    return this._systemInfo.length === 0
      ? (this._systemInfo.push({
          name: "No VEX Device Connected",
          type: g.TreeItemCollapsibleState.None,
          items: [],
        }),
        Promise.resolve(this._systemInfo))
      : t === void 0
      ? Promise.resolve(this._systemInfo)
      : Promise.resolve(t.items);
  }
  get deviceInfo() {
    return this._deviceInfo;
  }
};
var Ae = L(require("vscode"));
var _o = class {
  constructor(t, e) {
    this._context = t;
    this._vexcomInfo = e;
    this._visable = !1;
    this._isFirst = !0;
  }
  resolveWebviewView(t, e, o) {
    (this._view = t),
      (t.webview.options = {
        enableScripts: !0,
        localResourceRoots: [
          Ae.Uri.joinPath(this._context.extensionUri, "resources", "icons"),
          Ae.Uri.joinPath(this._context.extensionUri, "resources", "webviews"),
          Ae.Uri.joinPath(
            this._context.extensionUri,
            "dist",
            "webviews",
            "views"
          ),
          Ae.Uri.joinPath(
            this._context.extensionUri,
            "node_modules",
            "@vscode",
            "webview-ui-toolkit",
            "dist"
          ),
          Ae.Uri.joinPath(
            this._context.extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist"
          ),
          Ae.Uri.joinPath(
            this._context.extensionUri,
            "resources",
            "webviews",
            "libs"
          ),
          Ae.Uri.joinPath(this._context.extensionUri, "webviews", "view"),
          Ae.Uri.joinPath(
            this._context.extensionUri,
            "node_modules",
            "fomantic-ui-css"
          ),
          Ae.Uri.joinPath(this._context.extensionUri, "resources", "icons"),
        ],
      }),
      t.onDidChangeVisibility(() => {}),
      (t.webview.html = this._getHtmlForWebview(t.webview)),
      t.webview.onDidReceiveMessage((s) => {
        switch (s.type) {
          case "newProjectBtn": {
            console.log("New Project Button Clicked"),
              i.Extension.Command.newProject();
            break;
          }
          case "importProjectBtn": {
            console.log("Import Project Button Clicked"),
              i.Extension.Command.importProject();
            break;
          }
          case "vexcomVersion": {
            console.log("VEXCOM VERSION Called");
            break;
          }
          case "setContext":
            return i.Extension.Context.setDebug(!0);
          case "isFirst":
            this._view.webview.postMessage({
              type: s.type,
              result: this._isFirst,
            }),
              (this._isFirst = !1);
        }
      }),
      t.onDidDispose(() => {
        console.log("Home View Disposed");
      }),
      this.resetProgressState();
  }
  updateProgress(t, e = !0) {
    (this._lastMsg = t),
      !(!this._view || !this._view.visible) &&
        this._view.webview.postMessage({
          type: "progress-update",
          content: t,
          visable: e,
        });
  }
  showProgress(t) {
    (this._visable = t),
      this._view &&
        this._view.webview.postMessage({
          type: "progress-visable",
          visable: t,
        });
  }
  resetProgressState() {
    (this._visable = !1),
      this._view.webview.postMessage({
        type: "progress-reset",
      });
  }
  _getHtmlForWebview(t) {
    let e = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "dist",
          "webviews",
          "views",
          "homeView.js"
        )
      ),
      o = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "webviews",
          "libs",
          "jquery",
          "jquery.js"
        )
      ),
      s = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "webviews",
          "style",
          "reset.css"
        )
      ),
      n = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "webviews",
          "style",
          "vscode.css"
        )
      ),
      a = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "webviews",
          "style",
          "homeView.css"
        )
      ),
      r = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "node_modules",
          "@vscode",
          "webview-ui-toolkit",
          "dist",
          "toolkit.js"
        )
      ),
      c = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "node_modules",
          "@vscode",
          "codicons",
          "dist",
          "codicon.css"
        )
      ),
      l = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "webviews",
          "style",
          "progress.css"
        )
      ),
      d = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "node_modules",
          "fomantic-ui-css",
          "semantic.css"
        )
      ),
      m = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "node_modules",
          "fomantic-ui-css",
          "semantic.js"
        )
      ),
      w = t.asWebviewUri(
        Ae.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "icons",
          "vexai.svg"
        )
      ),
      b = i.Extension.version(),
      C = ir();
    return `<!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <!--
                    Use a content security policy to only allow loading images from https or from our extension directory,
                    and only allow scripts that have a specific nonce.
                -->
                <!--
                <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${t.cspSource}; script-src 'nonce-${C}';">
                --> 
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
        
                <!--Semantic-->

                <script nonce="${C}" src="${o}"><\/script>
                <link href="${d}"     rel="stylesheet">

                <link href="${s}" rel="stylesheet">
                <link href="${a}"  rel="stylesheet">
                <link href="${c}"     rel="stylesheet">
                <link href="${l}"     rel="stylesheet">

                <script nonce="${C}" src="${m}"><\/script>
                <script nonce="${C}" type="module" src="${r}"><\/script>
                <script nonce="${C}" src="${e}"><\/script>


                <title>Vex</title>
            </head>
            <body>
                <div style="display:flex; flex-direction:column; height:100%;">
                    <vscode-button class="strectch-row buttonMargin" id="newProjectBtn" appearance="primary" aria-label="New Projet" >New Project</vscode-button>
                    <vscode-button class="strectch-row buttonMargin" id="importProjectBtn" appearance="primary" aria-label="Import Project">Import Project</vscode-button>
                    <div class="strectch-column-div"></div>
                    <div style="display:flex; flex-direction:column; width:100%; height:100%;"></div>
                    <div id="progList" style="noselect padding-left:5px; padding-right:5px;"></div>
                    <div class="page-footer noselect">
                        <h4 id="extVersion" class="version" style="font-weight:bold;">${b}</h4>
                        <h4 id="vexcomVersion" class="version" style="font-weight:bold;">vexcom:${this._vexcomInfo.app.version}</h4>
                    </div>
                </div>

            </body>
            </html>`;
  }
};
_o.viewType = "vex.vex-sidebar-home-webview";

function ir() {
  let _ = "",
    t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let e = 0; e < 32; e++)
    _ += t.charAt(Math.floor(Math.random() * t.length));
  return _;
}
var Ce = L(require("vscode"));
var ui = L(require("os")),
  zo = require("fs");
var eo = L(require("vscode-textmate")),
  lo = L(require("vscode-oniguruma")),
  gs = L(require("json5")),
  Re = L(require("vscode")),
  Pt = L(require("fs")),
  di = L(require("os")),
  pi = L(require("path"));
var Ho = class {
  constructor() {
    (this._wasmBin = Pt.readFileSync(
      Re.Uri.joinPath(
        i.Extension.context.extensionUri,
        "node_modules",
        "vscode-oniguruma",
        "release",
        "onig.wasm"
      ).fsPath
    ).buffer),
      (this._vscodeOnigurumaLib = lo.loadWASM(this._wasmBin).then(() => ({
        createOnigScanner(t) {
          return new lo.OnigScanner(t);
        },
        createOnigString(t) {
          return new lo.OnigString(t);
        },
      }))),
      this._registerLanguages(),
      this._updateBackupColorThemeList(),
      this.updateActiveTheme(),
      console.log(this.activeColorThemeId),
      this.setTheme({
        name: this._currentColorTheme.label,
        settings: this._currentColorTheme.tokenColors,
      }),
      Re.window.onDidChangeActiveColorTheme(async (t) => {
        await i.Utils.asyncSleep(500),
          console.log(t),
          this.updateActiveTheme(),
          console.log(this._currentColorTheme),
          console.log(this?._registry?.getColorMap()),
          this.setTheme({
            name: this._currentColorTheme.label,
            settings: this._currentColorTheme.tokenColors,
          }),
          console.log(this?._registry?.getColorMap());
      });
  }
  _registerLanguages() {
    this._registry = new eo.Registry({
      onigLib: this._vscodeOnigurumaLib,
      loadGrammar: this._loadGrammer,
    });
  }
  async _loadGrammer(t) {
    let e = null,
      o,
      s;
    switch (t) {
      case "source.cpp":
        Re.extensions.all,
          (o = Re.extensions.getExtension("vscode.cpp")),
          (o = i.Backup.Extensions.getExtension("vscode.cpp")),
          console.log(o),
          (s = o.packageJSON.contributes.grammars.filter(
            (a) => a.scopeName === t
          )[0]),
          (e = Re.Uri.joinPath(o.extensionUri, s.path));
        break;
      case "source.python":
        (o = Re.extensions.getExtension("vscode.python")),
          (o = i.Backup.Extensions.getExtension("vscode.python")),
          (s = o.packageJSON.contributes.grammars.filter(
            (a) => a.scopeName === t
          )[0]),
          console.log(s),
          (e = Re.Uri.joinPath(o.extensionUri, s.path));
        break;
      default:
        e = null;
        break;
    }
    if (!e || !Pt.existsSync(e.fsPath)) return null;
    let n = Pt.readFileSync(e.fsPath);
    return eo.parseRawGrammar(n.toString(), e.fsPath);
  }
  _updateColorThemeList() {
    let e = Re.extensions.all.filter(
        (s) => !!s.packageJSON?.contributes?.themes
      ),
      o = [];
    e.forEach((s) => {
      let n = s.packageJSON;
      n.contributes.themes.forEach((a) => {
        o.push({
          extensionId: n.id,
          label: a.label,
          id: a.id ? a.id : a.label,
          themeUri: Re.Uri.joinPath(s.extensionUri, a.path),
        });
      });
    }),
      (this._colorThemeList = o);
  }
  _updateBackupColorThemeList() {
    let e = i.Backup.Extensions.all.filter(
        (s) => !!s.packageJSON?.contributes?.themes
      ),
      o = [];
    e.forEach((s) => {
      let n = s.packageJSON;
      n.contributes.themes.forEach((a) => {
        o.push({
          extensionId: n.id,
          label: a.label,
          id: a.id ? a.id : a.label,
          themeUri: Re.Uri.joinPath(s.extensionUri, a.path),
        });
      });
    }),
      (this._colorThemeListBackup = o);
  }
  get activeColorThemeId() {
    return Re.workspace.getConfiguration().get("workbench.colorTheme");
  }
  updateActiveTheme() {
    let t = this.activeColorThemeId,
      e = this._colorThemeList?.filter((a) => a.id === t)[0];
    if (
      (e ||
        (this._updateColorThemeList(),
        (e = this._colorThemeList?.filter((a) => a.id === t)[0])),
      e || (e = this._colorThemeListBackup?.filter((a) => a.id === t)[0]),
      !e)
    )
      switch (Re.window.activeColorTheme.kind) {
        case Re.ColorThemeKind.Dark:
          e = this._colorThemeListBackup?.filter(
            (a) => a.id === "Default Dark+"
          )[0];
          break;
        case Re.ColorThemeKind.HighContrast:
          e = this._colorThemeListBackup?.filter(
            (a) => a.id === "Default Dark+"
          )[0];
          break;
        case Re.ColorThemeKind.Light:
          e = this._colorThemeListBackup?.filter(
            (a) => a.id === "Default High Contrast"
          )[0];
          break;
        case Re.ColorThemeKind.HighContrastLight:
          e = this._colorThemeListBackup?.filter(
            (a) => a.id === "Default High Contrast Light"
          )[0];
          break;
      }
    this._currentColorTheme = e ? this.getColorThemeJSON(e) : void 0;
    let o = this._currentColorTheme,
      s = this._currentColorTheme.tokenColors
        ? this._currentColorTheme.tokenColors
        : [],
      n = !!o?.include;
    for (; n; ) {
      let a = pi.dirname(e?.themeUri.path),
        r = Re.Uri.joinPath(Re.Uri.file(a), o?.include);
      console.log(Pt.existsSync(r.fsPath)),
        console.log(Pt.readFileSync(r.fsPath));
      let c = gs.parse(Pt.readFileSync(r.fsPath).toString());
      (s = (c.tokenColors ? c.tokenColors : []).concat(s)),
        c?.include ? ((o = c), (n = !0)) : ((o = void 0), (n = !1)),
        console.log(n);
    }
    (this._currentColorTheme.tokenColors = s),
      (this._currentColorTheme.label = e.label);
  }
  getColorThemeJSON(t) {
    if (!Pt.existsSync(t.themeUri.fsPath)) return;
    let e = new TextDecoder().decode(Pt.readFileSync(t.themeUri.fsPath));
    console.log(e);
    let o;
    try {
      o = gs.parse(e);
    } catch {
      o = void 0;
    }
    return o;
  }
  async loadGrammar(t) {
    this._grammar = await this._registry.loadGrammar(t);
  }
  async loadGrammarWithConfiguration(t) {}
  setTheme(t, e) {
    this?._registry?.setTheme(t, e),
      this?._registry?.getColorMap(),
      console.log(t, this?._registry?.getColorMap());
  }
  getColorMap(t, e) {
    this?._registry?.getColorMap();
  }
  getCSSRules() {
    let t = [],
      e = 1;
    this?._registry?.getColorMap().forEach((s) => {
      switch (e) {
        case 1:
          t.push(`.mtk${e} { color:var(--vscode-editor-foreground); }`);
          break;
        case 2:
          t.push(`.mtk${e} { color:var(--vscode-editor-background); }`);
          break;
        default:
          t.push(`.mtk${e} { color:${s}; }`);
          break;
      }
      e++;
    }),
      t.push(".mtki { font-style: italic; }"),
      t.push(".mtkb { font-weight: bold;  }"),
      t.push(
        ".mtku { text-decoration: underline; text-underline-position: under; }"
      ),
      t.push(".mtks { text-decoration: line-through; }"),
      t.push(
        ".mtks.mtku { text-decoration: underline line-through; text-underline-position: under; }"
      ),
      t.push(
        ".mtkback { background-color:var(--vscode-editor-hoverHighlightBackground); padding:15px; padding-top:10px; padding-bottom:10px; font-family: var(--vscode-editor-font-family); font-weight: var(--vscode-editor-font-weight); font-size: var(--vscode-editor-font-size);}"
      ),
      t.push(
        ".mtkback-inline { background-color:var(--vscode-editor-hoverHighlightBackground); padding-left:5px; padding-right:5px; }"
      );
    let o = "";
    return (
      t.forEach((s) => {
        o += `${s}${di.EOL}`;
      }),
      o
    );
  }
  textHighlight(t) {
    let e,
      o = [],
      s = eo.INITIAL,
      n = eo.INITIAL,
      a = "";
    for (let r = 0; r < [t].length; r++) {
      let c = [t][r],
        l = this._grammar.tokenizeLine(c, s),
        d = this._grammar.tokenizeLine2(c, n);
      console.log(`
Tokenizing line: ${l}`);
      let m = this._registry.getColorMap();
      e = d.tokens;
      for (let w = 0; w < l.tokens.length; w++) {
        let b = !1,
          C = l.tokens[w];
        for (let E = 0; E < d.tokens.length; E = E + 2)
          if (e[E] === C.startIndex) {
            let T = bt.getForeground(e[E + 1]),
              O = bt.getBackground(e[E + 1]),
              f = bt.getFontStyle(e[E + 1]),
              k = bt.getLanguageId(e[E + 1]),
              z = bt.getInlineStyleFromMetadata(e[E + 1], m),
              Z = bt.containsBalancedBrackets(e[E + 1]),
              S = bt.getPresentationFromMetadata(e[E + 1]),
              W = bt.getTokenType(e[E + 1]),
              V = bt.getClassNameFromMetadata(e[E + 1]);
            a = V;
            let X = `Text:'${t.substring(C.startIndex, C.endIndex)}'
                            ${C.scopes}
                            ${T}
                            ${O}
                            ${f}
                            ${k}
                            ${z}
                            ${T}
                            ${Z}
                            ${S}
                            ${W}`;
            console.log(X),
              o.push({
                html: `<span class="${V}">${t.substring(
                  C.startIndex,
                  C.endIndex
                )}</span>`,
              }),
              (b = !0);
            continue;
          }
        b ||
          o.push({
            html: `<span class="${a}">${t.substring(
              C.startIndex,
              C.endIndex
            )}</span>`,
          });
      }
      (s = l.ruleStack), (n = d.ruleStack);
    }
    return console.log(o), o;
  }
};
var bt = class {
  static getLanguageId(t) {
    return (t & 255) >>> 0;
  }
  static getTokenType(t) {
    return (t & 768) >>> 8;
  }
  static containsBalancedBrackets(t) {
    return (t & 1024) !== 0;
  }
  static getFontStyle(t) {
    return (t & 30720) >>> 11;
  }
  static getForeground(t) {
    return (t & 16744448) >>> 15;
  }
  static getBackground(t) {
    return (t & 4278190080) >>> 24;
  }
  static getClassNameFromMetadata(t) {
    let e = this.getForeground(t),
      o = "mtk" + e,
      s = this.getFontStyle(t);
    return (
      s & 1 && (o += " mtki"),
      s & 2 && (o += " mtkb"),
      s & 4 && (o += " mtku"),
      s & 8 && (o += " mtks"),
      o
    );
  }
  static getInlineStyleFromMetadata(t, e) {
    let o = this.getForeground(t),
      s = this.getFontStyle(t),
      n = `color: ${e[o]};`;
    s & 1 && (n += "font-style: italic;"), s & 2 && (n += "font-weight: bold;");
    let a = "";
    return (
      s & 4 && (a += " underline"),
      s & 8 && (a += " line-through"),
      a && (n += `text-decoration:${a};`),
      n
    );
  }
  static getPresentationFromMetadata(t) {
    let e = this.getForeground(t),
      o = this.getFontStyle(t);
    return {
      foreground: e,
      italic: Boolean(o & 1),
      bold: Boolean(o & 2),
      underline: Boolean(o & 4),
      strikethrough: Boolean(o & 8),
    };
  }
};
var nr = require("path"),
  ar = require("markdown-it"),
  Jc = require("highlight.js").default,
  cr = require("markdown-it-front-matter"),
  we = class {
    constructor(t) {
      this.v5PythonMdList = [];
      this.v5CppMdList = [];
      this.expPythonMdList = [];
      this.expCppMdList = [];
      this.iq2PythonMdList = [];
      this.iq2CppMdList = [];
      try {
        (this._context = t),
          (we._extensionUri = t.extensionUri),
          (we._grammar = new Ho()),
          Ce.window.onDidChangeActiveColorTheme((e) =>
            this.reloadOnThemeChange(e, this)
          );
      } catch (e) {
        console.error("VEX Command Help Error", e);
      }
    }
    async initMarkList() {
      (this.v5CppMdList = await this.buildMDList(
        i.Platform.V5,
        i.Language.cpp
      )),
        (this.v5PythonMdList = await this.buildMDList(
          i.Platform.V5,
          i.Language.python
        )),
        (this.expCppMdList = await this.buildMDList(
          i.Platform.EXP,
          i.Language.cpp
        )),
        (this.expPythonMdList = await this.buildMDList(
          i.Platform.EXP,
          i.Language.python
        )),
        (this.iq2CppMdList = await this.buildMDList(
          i.Platform.IQ2,
          i.Language.cpp
        )),
        (this.iq2PythonMdList = await this.buildMDList(
          i.Platform.IQ2,
          i.Language.python
        ));
    }
    async buildMDList(t, e) {
      let o = we.mdFolderNames.get(`${t}_${e}`)
        ? we.mdFolderNames.get(`${t}_${e}`)
        : void 0;
      if (!o) return [];
      let s = Ce.Uri.joinPath(
          this._context.extensionUri,
          "resources",
          "md",
          o,
          "en"
        ),
        n = [];
      return (0, zo.existsSync)(s.fsPath)
        ? ((await Ce.workspace.fs.readDirectory(s)).forEach((r) => {
            let c = Ce.Uri.joinPath(s, r[0], `${r[0]}.md`),
              d = new TextDecoder()
                .decode((0, zo.readFileSync)(c.fsPath))
                .split(ui.EOL),
              m = new RegExp(/(?<=\s*category:\s+)\w*(?=\s+)/),
              w = new RegExp(/(?<=\s*signature:\s+).*(?=\s*)/),
              b = new RegExp(/(?<=\s*device_class:\s+)\w*(?=\s+)/),
              C = new RegExp(/(?<=\s*description:\s+).*/);
            if (
              (w.test(d[1]) || console.log(d[1], m.exec(d[0])[0]),
              r[1] === Ce.FileType.Directory)
            ) {
              let E = "";
              w.test(d[1]) &&
                (E = w.exec(d[1])[0].replace(/\\n|\\t|pass/gi, ""));
              let T = {
                language: e,
                platform: t,
                mdUri: c,
                name: `${r[0]}`,
                category: m.test(d[0]) ? m.exec(d[0])[0] : "",
                signature: E,
                device_class: b.test(d[2]) ? b.exec(d[2])[0] : "",
                description: C.test(d[3]) ? C.exec(d[3])[0] : "",
                markdown: d.slice(4).join(`\r
`),
              };
              n.push(T);
            }
          }),
          n || [])
        : [];
    }
    async getActiveList(t, e) {
      return (
        await we._grammar.loadGrammar(`source.${e}`),
        t === i.Platform.EXP && e === i.Language.cpp
          ? this.expCppMdList
          : t === i.Platform.EXP && e === i.Language.python
          ? this.expPythonMdList
          : t === i.Platform.V5 && e === i.Language.cpp
          ? this.v5CppMdList
          : t === i.Platform.V5 && e === i.Language.python
          ? this.v5PythonMdList
          : t === i.Platform.IQ2 && e === i.Language.cpp
          ? this.iq2CppMdList
          : t === i.Platform.IQ2 && e === i.Language.python
          ? this.iq2PythonMdList
          : []
      );
    }
    async reloadOnThemeChange(t, e) {
      we._view.dispose(),
        await i.Utils.asyncSleep(500),
        await we._grammar.updateActiveTheme(),
        we._currentMarkdownFile && (await e.Show(we._currentMarkdownFile));
    }
    async Show(t) {
      if (
        ((we._currentMarkdownFile = t),
        console.log("resolve Webview"),
        we._isRunning)
      ) {
        (this._panel.webview.html = we._getHtmlForWebview(
          this._panel.webview,
          t
        )),
          this._panel.reveal(this._panel.viewColumn);
        return;
      }
      return (
        (this._panel = Ce.window.createWebviewPanel(
          we.viewType,
          "Vex Command Help",
          {
            viewColumn: Ce.ViewColumn.Two,
            preserveFocus: !1,
          }
        )),
        (we._isRunning = !0),
        (we._projectOptionsList = Co),
        await we.resolveWebviewView(this._panel, t)
      );
    }
    static async resolveWebviewView(t, e) {
      console.log("resolve Webview"), (this._view = t);
      let o = !1;
      console.log("resolve Webview");
      let s = {
        event: "create",
        projectPath: "",
        projectIndex: -1,
        vexSettings: {
          extension: {
            json: 1,
            version: "",
          },
          project: {
            sdkVersion: "",
            creationDate: "",
            description: "",
            language: void 0,
            name: "",
            platform: void 0,
            slot: 1,
          },
        },
        zipName: "",
      };
      for (
        t.webview.options = {
          enableScripts: !0,
          localResourceRoots: [
            Ce.Uri.joinPath(we._extensionUri, "resources", "icons"),
            Ce.Uri.joinPath(we._extensionUri, "dist", "views"),
            Ce.Uri.joinPath(
              we._extensionUri,
              "node_modules",
              "@vscode",
              "webview-ui-toolkit",
              "dist"
            ),
            Ce.Uri.joinPath(
              we._extensionUri,
              "node_modules",
              "@vscode",
              "codicons",
              "dist"
            ),
            Ce.Uri.joinPath(we._extensionUri, "resources", "webviews", "libs"),
            Ce.Uri.joinPath(we._extensionUri, "resources", "md"),
          ],
        },
          t.webview.html = we._getHtmlForWebview(t.webview, e),
          t.webview.onDidReceiveMessage((n) => {
            if ((console.log("Provider Recieved", n), !!n))
              switch (n.type) {
                case "cancelBtn": {
                  (we._isRunning = !1),
                    (s.event = "cancel"),
                    (s.projectIndex = -1),
                    (s.zipName = ""),
                    (s.vexSettings = void 0),
                    t.dispose();
                  break;
                }
              }
          }),
          t.onDidDispose(() => {
            we._isRunning && (console.log("Disposed"), (s.event = "disposed")),
              (o = !0),
              (we._isRunning = !1);
          });
        !o;

      )
        await new Promise((n) => setTimeout(n, 500));
      return console.log("Create Project DONE"), s;
    }
    static _getHtmlForWebview(t, e) {
      let o = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "libs",
            "jquery",
            "jquery.js"
          )
        ),
        s = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "highlight.css"
          )
        ),
        n = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "reset.css"
          )
        ),
        a = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "markdown.css"
          )
        ),
        r = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "webviews",
            "style",
            "main.css"
          )
        ),
        c = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "md",
            "v5",
            "sensing_vision_objects_angle.md"
          )
        ),
        l = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "resources",
            "md",
            "v5",
            "_sensing_vision_objects_angle.html"
          )
        ),
        d = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "webview-ui-toolkit",
            "dist",
            "toolkit.js"
          )
        ),
        m = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.css"
          )
        ),
        w = t.asWebviewUri(
          Ce.Uri.joinPath(
            this._extensionUri,
            "node_modules",
            "@vscode",
            "codicons",
            "dist",
            "codicon.svg"
          )
        ),
        b = (f) => {
          f.core.ruler.push("source_map_data_attribute", (S) => {
            console.log(S.tokens);
            for (let W of S.tokens)
              W.tag === "p"
                ? (console.log(W.type),
                  W.attrJoin("style", "color:var(--vscode-foreground);"))
                : W.tag === "code"
                ? console.log(W.type)
                : W.map &&
                  W.type !== "inline" &&
                  (W.attrSet("data-line", String(W.map[0])),
                  W.attrJoin("class", "code-line"),
                  W.attrJoin("dir", "auto")),
                console.log(W?.children);
          });
          let k = f.renderer.rules.html_block;
          k &&
            (f.renderer.rules.html_block = (S, W, V, X, ye) =>
              `<div ${ye.renderAttrs(S[W])} ></div>
` + k(S, W, V, X, ye));
          let z = t,
            Z = f.renderer.rules.image;
          (f.renderer.rules.image = (S, W, V, X, ye) => {
            let se = S[W];
            se.attrJoin("class", "loading");
            let G = se.attrGet("src");
            if (G) {
              X.containingImages?.push({
                src: G,
              });
              let re = dr(G);
              if (
                (se.attrSet("id", `image-hash-${re}`), !se.attrGet("data-src"))
              ) {
                let fe = Ce.Uri.file(nr.dirname(e.mdUri.fsPath)),
                  me = z.asWebviewUri(Ce.Uri.joinPath(fe, G));
                se.attrSet("src", me.toString()), se.attrSet("data-src", G);
              }
            }
            return Z ? Z(S, W, V, X, ye) : ye.renderToken(S, W, V);
          }),
            console.log(f.renderer.rules.code_inline),
            (f.renderer.rules.code_inline = (S, W, V, X, ye) => {
              console.log(S, W, V, X, ye);
              let se = [];
              S[W].content.includes("%") && !S[W].content.includes('"')
                ? (se = we._grammar.textHighlight(`"${S[W].content}"`))
                : (se = we._grammar.textHighlight(S[W].content));
              let G = "";
              return (
                se.forEach((re) => {
                  G += re.html;
                }),
                `<code class="mtkback-inline">${G}</code>`
              );
            });
        },
        C = ar({
          html: !0,
          highlight: (f, k) => {
            let z = we._grammar.textHighlight(f),
              Z = "";
            z.forEach((W) => {
              Z += W.html;
            }),
              console.log(Z);
            let S = 100 - Z.length;
            return `<pre class="mtkback">${Z.padEnd(S, " ")}</pre>`;
          },
        });
      C.linkify.set({
        fuzzyLink: !1,
      });
      let E;
      cr(
        {
          block: {
            ruler: {
              before: (f, k, z) => {
                E = z;
              },
            },
          },
        },
        () => {}
      ),
        C.block.ruler.before("fence", "front_matter", E, {
          alt: ["paragraph", "reference", "blockquote", "list"],
        });
      let T = C.use(b).render(e.markdown),
        O = lr();
      return `<!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <!--
                        Use a content security policy to only allow loading images from https or from our extension directory,
                        and only allow scripts that have a specific nonce.
                    -->
                    <!--
                    <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${
                      t.cspSource
                    }; script-src 'nonce-${O}';">
                    --> 
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">

                    




                    <title>Create new vex project</title>
                    <style>
                        ${this._grammar.getCSSRules()}
                    </style>

                </head>


                <body>
                    ${T}
                </body>
            </html>`;
    }
  },
  Rt = we;
(Rt.viewType = "general.commandHelp"), (Rt._isRunning = !1);
((t) =>
  (t.mdFolderNames = new Map([
    ["V5_cpp", "V5 CPP"],
    ["V5_python", "V5 Python"],
    ["EXP_cpp", "EXP CPP"],
    ["EXP_python", "EXP Python"],
    ["IQ2_cpp", "IQ CPP"],
    ["IQ2_python", "IQ Python"],
  ])))(Rt || (Rt = {}));

function lr() {
  let _ = "",
    t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let e = 0; e < 32; e++)
    _ += t.charAt(Math.floor(Math.random() * t.length));
  return _;
}

function mi(_, t) {
  return ((t << 5) - t + _) | 0;
}

function dr(_) {
  let t = mi(149417, 0);
  for (let e = 0, o = _.length; e < o; e++) t = mi(_.charCodeAt(e), t);
  return t;
}
var zt = L(require("path")),
  ze = L(require("os")),
  gi = L(require("fs"));
var Do;
((gr) => {
  let _,
    t,
    e,
    o,
    s,
    n,
    a,
    r,
    c,
    l,
    d,
    m,
    w = !1,
    b = !1,
    C = !1,
    E;
  async function T(u, v) {
    (i.Extension.context = u),
      (_ = u),
      (t = v),
      await i.Extension.setVexlogColor();
    let P = await new x(i.Extension.getVexcomUri(_).fsPath, "").getVersion();
    V(i.Utils._toCommandResponse(P));
    let y = JSON.parse(P.stdout);
    t.appendLine(`VEXCOM Version:        ${y.app.version} ${y.app.date}`),
      t.appendLine("");
    let D = (q) => t.appendLine(`${q}`);
    (n = new Xo(_)), (a = new _o(_, y));
    let H =
      p.workspace
        .getConfiguration()
        .get(
          i.Extension.Settings.enableAI3dCameraUserTerminalID,
          p.ConfigurationTarget.Global
        )
        .toString() === "Enable";
    p.window.registerTreeDataProvider("vex-sidebar-view", n),
      p.window.registerWebviewViewProvider("vex-sidebar-home-webview", a),
      (r = new Rt(_)),
      r.initMarkList(),
      (e = new ce(_, D)),
      (o = new Ke(_, D));
    let A = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.hostNameID, p.ConfigurationTarget.Global)
        .toString(),
      ge = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.portID, p.ConfigurationTarget.Global);
    if (
      ((E = new Ht(
        {
          port: ge,
          host: A,
        },
        D
      )),
      p.workspace
        .getConfiguration()
        .get(
          i.Extension.Settings.enableWebsocketServerID,
          p.ConfigurationTarget.Global
        )
        .toString() === "Enable")
    ) {
      d?.write(`Starting VEX Websocket ${E.websocketServer.address()}`);
      let q = p.workspace
          .getConfiguration()
          .get(i.Extension.Settings.hostNameID, p.ConfigurationTarget.Global)
          .toString(),
        Y = p.workspace
          .getConfiguration()
          .get(i.Extension.Settings.portID, p.ConfigurationTarget.Global);
      E.start({
        port: Y,
        host: q,
      });
    }
    E.on("connection", (q, Y) => {
      let Oe = E.deviceWSList.concat(E.vscodeWSList);
      if (Y.url.includes(E.deviceURL)) {
        let pe = ee.colorText(
          `Device Websocket Connection: ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}`,
          ee.TextColors.green
        );
        d.write(`${pe}\r
`),
          q.on("message", (ve) => {
            let mt = ee.colorText(
              `ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}->`,
              ee.TextColors.cyan
            );
            d.write(`${mt}${ve}`);
          });
      } else if (Y.url.includes(E.vscodeURL)) {
        let pe = ee.colorText(
          `VEX Command Websocket Connection: ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}`,
          ee.TextColors.green
        );
        d.write(`${pe}\r
`),
          q.on("message", (ve) => {
            let mt = ee.colorText(
                `ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}->`,
                ee.TextColors.blue
              ),
              uo = ve.toString().split(" "),
              ss = uo.shift().toString();
            p.commands.executeCommand(ss, uo).then((go) => {
              q.send(JSON.stringify(go));
            }),
              d.write(`${mt}${ve}\r
`);
          });
      }
      q.on("close", () => {
        let pe;
        Y.url.includes(E.deviceURL)
          ? (pe = ee.colorText(
              `Device Websocket Disconnected: ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}`,
              ee.TextColors.red
            ))
          : Y.url.includes(E.vscodeURL) &&
            (pe = ee.colorText(
              `VEX Command Websocket Disconnected: ws://${Y.socket.remoteAddress}:${Y.socket.remotePort}`,
              ee.TextColors.red
            )),
          d?.write(`${pe}\r
`);
      });
    }),
      (s = new Kt(_)),
      (c = new Me(_)),
      o.On("Build-Data", (q) => {
        l.writeBuildText(q);
      }),
      o.On("Build-Errors", (q, Y) => {
        switch (q) {
          case Ke.BuildErrorCodes.NOT_DEFINED_SDK:
          case Ke.BuildErrorCodes.MISSING_SDK:
            o.selectedProject.readProjectSettings().project.language === "cpp"
              ? o.checkCppSdk(o.selectedProject)
              : o.selectedProject.readProjectSettings().project.language ===
                  "python" && o.checkPythonSdk(o.selectedProject),
              l.write(Y);
            break;
          case Ke.BuildErrorCodes.MAKE_DOES_NOT_EXIST:
          case Ke.BuildErrorCodes.TOOLCHAIN_DOES_NOT_EXIST:
          case Ke.BuildErrorCodes.NOT_DEFINED_TOOLCHAIN:
            o.checkToolchain(!0), l.write(Y);
            break;
          case Ke.BuildErrorCodes.COMPILER_ERROR:
            l.writeBuildErrorText(Y);
            break;
          default:
            l.write(Y);
        }
      }),
      o.On("Build-Exit", (q, Y) => {
        q === void 0 || q !== 0
          ? t.appendLine(
              `[Command]: ${Y} Failed: make process closed with exit code : ${q}`
            )
          : t.appendLine(`[Command]: ${Y} Finished: Exit Code ${q}`),
          l.write(`\r
`);
      }),
      setInterval(async () => {
        if (
          (e.selectedDevice &&
            p.window.state.focused &&
            (e.selectedDevice instanceof Je
              ? n.refresh(e.selectedDevice, [e.selectedAIDevice])
              : kt()),
          e.selectedAIDevice && p.window.state.focused && !Qe)
        )
          if (e.selectedAIDevice instanceof _e)
            if (!e.selectedAIDevice.isAlive)
              V(await e.selectedAIDevice.checkAlive(), !1),
                n.refresh(e.selectedDevice, [e.selectedAIDevice]);
            else
              try {
                Zo();
              } catch (q) {
                console.log(q);
              }
          else
            try {
              Zo();
            } catch (q) {
              console.log(q);
            }
      }, 3e3),
      e.on("VEX_Device_Detected", re),
      e.on("VEX_Device_Disconnected", fe),
      e.on("VEX_DFU_Device_Detected", me),
      e.on("VEX_DFU_Device_Disconnected", ue),
      _.subscriptions.push(p.commands.registerCommand(Me.slotCmdId, ke)),
      _.subscriptions.push(p.commands.registerCommand(Me.playCmdId, Wo)),
      _.subscriptions.push(p.commands.registerCommand(Me.stopCmdId, Go)),
      _.subscriptions.push(p.commands.registerCommand(Me.buildCmdId, Ko)),
      _.subscriptions.push(p.commands.registerCommand(Me.listDevicesCmdId, qo)),
      _.subscriptions.push(
        p.commands.registerCommand(Me.selectProjectCmdId, K)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(Me.selectPythonCmdId, po)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.buildID, he)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.cleanID, De)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.rebuildID, Le)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.newProjectID, Wt)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.importID, So)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.settingUIID, vs)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.eraseID, Jo)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.downloadID, Te)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.systemInfoID, kt)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.screenGrabID, fs)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.brainNameID, bs)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.teamNumberID, ws)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.batteryMedicID, xs)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.systemUpdateVEXosID, Eo)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.systemUpdatePythonVmID,
          Ps
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.controllerUpdateFirmwareID,
          es
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.dfuUpdateFirmwareID, Vo)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.uploadEventLogID, hs)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.installDrivers, Us)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.vexCommandHelpID, Is)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.vexCommandHelpShowAllID,
          ts
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.downloadSDKID, _s)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.downloadToolchainID, Q)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.clearLogTerminalID, os)
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.clearInterativeTerminalID,
          bi
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.createNewTerminalSetID,
          wi
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.controllerUpdateFirmwareAtmelID,
          Ii
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.controllerUpdateFirmwareRadioDEVID,
          Ci
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.controllerUpdateFirmwareDEVID,
          Pi
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.brainUpdateFirmwareDEVID,
          _i
        )
      ),
      _.subscriptions.push(
        p.commands.registerCommand(i.Extension.Command.downloadAI, async () => {
          if (!(e.selectedAIDevice instanceof _e)) return;
          let q = p.workspace
              .getConfiguration()
              .get(
                i.Extension.Settings.aiCameraHomeID,
                p.ConfigurationTarget.Global
              )
              .toString(),
            Y = p.Uri.file(q),
            Oe = {
              title: "Update Controller Radio",
              defaultUri: Y,
              canSelectFolders: !1,
              canSelectFiles: !0,
              canSelectMany: !1,
              filters: {
                deb: ["deb"],
              },
            },
            pe = await p.window.showOpenDialog(Oe);
          if (!pe) {
            p.window.showWarningMessage("No VEXOS File Selected");
            return;
          }
          let ve = zt.basename(pe[0].fsPath),
            mt = p.Uri.file(`/home/root/${ve}`),
            yt = await e.selectedAIDevice.downloadApp(pe[0], mt);
          V(yt);
        })
      );
    let Qe = !1;
    _.subscriptions.push(
      p.commands.registerCommand(
        i.Extension.Command.download3DApp,
        async (q) => {
          if (e.selectedAIDevice instanceof _e)
            try {
              if (!q || Qe) return;
              let Y = e.selectedAIDevice.systemInfo.apps;
              (Qe = !0), console.log(q);
              let Oe = p.workspace
                  .getConfiguration()
                  .get(
                    i.Extension.Settings.aiCameraHomeID,
                    p.ConfigurationTarget.Global
                  )
                  .toString(),
                pe = await i.Extension.ResourceManager.getVEXaiAppVersions(
                  q.name,
                  p.Uri.file(Oe)
                ),
                ve = JSON.parse(pe.json),
                mt = "";
              ve.local.catalog.includes(ve.online.latest) ||
                (await i.Extension.ResourceManager.downloadVEXaiApp(q.name));
              let yt = await e.selectedAIDevice.clear();
              if (
                (V(yt, !1),
                Y.forEach(async (Nt) => {
                  if (
                    e.selectedAIDevice instanceof _e &&
                    Nt.Package !== "vexupdate" &&
                    !(Nt.Package === q.name && q.appMissing)
                  ) {
                    let vo = await e.selectedAIDevice.systemCtlService(
                      `${Nt.Package}.service`,
                      "stop"
                    );
                    V(vo, !1);
                  }
                }),
                !q.appMissing)
              ) {
                let Nt = q.name + ".service",
                  vo = await e.selectedAIDevice.removeApp(Nt);
                V(vo, !1);
              }
              (pe = await i.Extension.ResourceManager.getVEXaiAppVersions(
                q.name,
                p.Uri.file(Oe)
              )),
                (ve = JSON.parse(pe.json));
              let uo = zt.basename(ve.local.latest),
                ss = p.Uri.joinPath(p.Uri.file(Oe), "3d", "apps", uo + ".deb"),
                go = p.Uri.file(`/home/root/${uo}.deb`),
                ys = await e.selectedAIDevice.downloadApp(ss, go);
              if ((V(ys), ys.statusCode === F.StatusCodes.port_not_open)) {
                Qe = !1;
                return;
              }
              (pe = await e.selectedAIDevice.installApp(go)),
                JSON.parse(pe.json).exitcode === 0
                  ? (V(pe, !1),
                    p.window.showInformationMessage("VEXAI: Install Success"))
                  : V(pe),
                Y.forEach(async (Nt) => {
                  if (Nt.Package !== "vexupdate") {
                    if (!(e.selectedAIDevice instanceof _e)) return;
                    let vo = await e.selectedAIDevice.systemCtlService(
                      `${Nt.Package}.service`,
                      "start"
                    );
                    V(vo, !1);
                  }
                });
              let Di = await e.selectedAIDevice.removeFile(go.path);
              V(Di);
              let Ui = await e.selectedAIDevice.systemCtlService(
                q.name,
                "start"
              );
              V(Ui), kt(), (Qe = !1);
            } catch (Y) {
              console.log(Y), (Qe = !1);
            }
        }
      )
    ),
      _.subscriptions.push(
        p.commands.registerCommand(
          i.Extension.Command.TEST_COMMAND,
          async () => {
            if (!(e.selectedAIDevice instanceof _e) || !e.selectedAIDevice)
              return;
            let q = await e.selectedAIDevice.resetTerminal();
            V(q);
          }
        )
      ),
      await Ds(),
      o
        .setup()
        .then(async () => {
          let q = p.Uri.joinPath(_.globalStorageUri, "buildText");
          if (
            (ee.Log.setBuildLogFileHome(q),
            ee.Log.clearTempLog(),
            o.selectedProject)
          ) {
            i.Extension.Context.setIsValidProject(!0),
              (c.selectProjectBtn.text = o.selectedProject.name);
            let Y = o.selectedProject.readProjectSettings();
            Y.project.language === i.Language.python &&
              ((c.selectPythonFileBtn.text = `$(python-qp)${zt.basename(
                Y.project.python.main
              )}`),
              c.selectPythonFileBtn.show()),
              (c.selectSlotBtn.text = `$(vex-slot) Slot ${Y.project.slot}`),
              c.deviceListBtn.show(),
              c.selectSlotBtn.show(),
              c.buildBtn.show(),
              c.playBtn.show(),
              c.stopBtn.show(),
              c.selectProjectBtn.show();
            let Oe = !1;
            if (
              (p.window.terminals.forEach((ve) => {
                (ve.name === "Log" || ve.name === "Interactive Terminal") &&
                  (ve.dispose(), (Oe = !0));
              }),
              Oe && (await i.Utils.asyncSleep(500)),
              (l = new ee.Log()),
              p.workspace
                .getConfiguration()
                .get(
                  i.Extension.Settings.enableUserTerminalID,
                  p.ConfigurationTarget.Global
                )
                .toString() === "Enable"
                ? ((d = new ee.Interactive("Interactive Terminal", l.terminal)),
                  l.terminal.show(),
                  d.terminal.show())
                : l.terminal.show(),
              !s.exist)
            ) {
              let ve = await s.download();
              ve.statusCode !== 200 && V(ve);
            }
          } else i.Extension.Context.setIsValidProject(!1);
          Cs();
        })
        .then(async () => {})
        .catch((q) => {
          t.appendLine(`${q}`);
        })
        .finally(() => {
          e.startSearch();
        }),
      p.workspace.onDidRenameFiles((q) => {
        if (!o.selectedProject) return;
        let Y = o.selectedProject.readProjectSettings();
        if (Y.project.language !== "python") return;
        let Oe = Y.project.python.main.replace(zt.sep, "\\");
        (Oe = Y.project.python.main.replace(String.fromCharCode(92), "\\")),
          (Oe = Y.project.python.main.replace(String.fromCharCode(47), "\\"));
        let pe = p.Uri.joinPath(o.selectedProject.projectUri, Oe);
        q.files.forEach((ve) => {
          ve.oldUri.fsPath === pe.fsPath &&
            ve.oldUri.fsPath.includes(".py") &&
            ve.newUri.fsPath.includes(".py") &&
            ve.oldUri.fsPath.includes(o.selectedProject.projectUri.fsPath) &&
            ((Y.project.python.main = p.workspace.asRelativePath(ve.newUri)),
            o.selectedProject.writeProjectSettings(Y),
            (c.selectPythonFileBtn.text = `$(python-qp)${zt.basename(
              Y.project.python.main
            )}`),
            o.selectedProject.writeProjectSettings(Y));
        });
      }),
      p.workspace.onDidChangeConfiguration(z);
  }
  gr.setup = T;
  async function O() {
    a.resetProgressState(),
      e.selectedDevice &&
        e.selectedDevice instanceof J &&
        e.selectedDevice.userPort.close(),
      e.selectedAIDevice &&
        e.selectedAIDevice instanceof _e &&
        (e.selectedAIDevice.userPort.close(),
        e.selectedAIDevice.comsPort.close()),
      E.stop();
  }
  gr.shutDown = O;
  async function f() {}
  gr.postExtensionSetup = f;
  async function k(u = !0) {
    if (!(e.selectedAIDevice instanceof _e) || !e.selectedAIDevice) return;
    u &&
      (m.writeLine(""),
      m.writeLine(""),
      m.writeLine("Reset Terminal", ee.TextColors.yellow),
      m.writeLine(""));
    let v = await e.selectedAIDevice.resetTerminal();
    V(v);
  }
  gr.resetAITerminal = k;
  async function z(u) {
    i.Extension.Settings.getChangeSettingsList(u).forEach((h) => {
      switch (h) {
        case i.Extension.Settings.enableUserTerminalID:
          Z();
          break;
        case i.Extension.Settings.enableAI3dCameraUserTerminalID:
          i.Extension.Context.isDevEnabled && S();
          break;
        case i.Extension.Settings.enableWebsocketServerID:
          W();
          break;
        default:
          break;
      }
    });
  }
  async function Z() {
    if (
      !o.selectedProject ||
      !(e.selectedDevice instanceof J) ||
      e.selectedDevice.bootMode !== I.BootMode.app
    )
      return;
    let v =
      p.workspace
        .getConfiguration()
        .get(
          i.Extension.Settings.enableAI3dCameraUserTerminalID,
          p.ConfigurationTarget.Global
        )
        .toString() === "Enable";
    if (d && !v) {
      if (
        e.selectedDevice?.userPort?.isOpen &&
        e.selectedDevice.bootMode === I.BootMode.app
      ) {
        let h = e.selectedDevice;
        e.selectedDevice?.userPort?.close((P) => ye(P, h));
      }
      if ((d.terminal.dispose(), (d = void 0), e.selectedDevice)) {
        let h =
          e.selectedDevice.robotName === ""
            ? ""
            : `(${e.selectedDevice.robotName}) ${e.selectedDevice.user}`;
        p.window.showInformationMessage(
          `Disabled Interactive Terminal Success: ${e.selectedDevice.platform} ${e.selectedDevice.device} ${h}`
        );
      }
    } else if (!d && v)
      if (e.selectedDevice)
        await (async () => {
          if (!(e.selectedDevice instanceof J)) return;
          (e.selectedDevice?.userPort ||
            e.selectedDevice.bootMode === I.BootMode.app) &&
            (e.selectedDevice?.userPort?.close(ye),
            await i.Utils.asyncSleep(1e3)),
            l?.terminal?.dispose(),
            d?.terminal?.dispose(),
            (l = new ee.Log()),
            (d = new ee.Interactive("Interactive Terminal", l.terminal));
          let P = ee.Log.read();
          await i.Utils.asyncSleep(500),
            l.writeLogText(P),
            l.terminal.show(),
            d.terminal.show(),
            e.selectedDevice?.userPort?.open(X),
            await i.Utils.asyncSleep(1e3),
            d &&
              (d.registerCB("Input", (D) => {
                e.selectedDevice instanceof J &&
                  e.selectedDevice.userPort.write(D);
              }),
              e.selectedDevice.userPort.registerCallback(
                "OnRecieveData",
                (D) => {
                  D !== void 0 &&
                    (d?.write(D), E.deviceWSList.forEach((U) => U[0].send(D)));
                }
              ));
          let y =
            e.selectedDevice.robotName === ""
              ? ""
              : `(${e.selectedDevice.robotName}) ${e.selectedDevice.user}`;
          p.window.showInformationMessage(
            `Enable Interactive Terminal Success: ${e.selectedDevice.platform} ${e.selectedDevice.device} ${y}`
          );
        })().catch(async (P) => {
          p.window.showErrorMessage(
            `Enable Interactive Terminal Error: ${P.message}`
          ),
            await p.workspace
              .getConfiguration()
              .update(
                i.Extension.Settings.enableUserTerminalID,
                "Disable",
                p.ConfigurationTarget.Global
              );
        });
      else {
        l?.terminal && l?.terminal?.dispose(),
          (l = new ee.Log()),
          (d = new ee.Interactive("Interactive Terminal", l.terminal));
        let h = ee.Log.read();
        await i.Utils.asyncSleep(500),
          l.writeLogText(h),
          l.terminal.show(),
          d.terminal.show();
      }
  }
  async function S() {
    if (
      !(e.selectedAIDevice instanceof _e) ||
      e.selectedAIDevice.bootMode !== I.BootMode.app
    )
      return;
    let v =
      p.workspace
        .getConfiguration()
        .get(
          i.Extension.Settings.enableAI3dCameraUserTerminalID,
          p.ConfigurationTarget.Global
        )
        .toString() === "Enable";
    if (m && !v) {
      if (
        e.selectedAIDevice?.userPort?.isOpen &&
        e.selectedAIDevice.bootMode === I.BootMode.app
      ) {
        let h = e.selectedDevice;
        e.selectedAIDevice?.userPort?.close((P) => G(P, h));
      }
      if (
        (m.terminal.dispose(),
        (m = void 0),
        e.selectedAIDevice instanceof _e && e.selectedAIDevice)
      ) {
        let h =
          e.selectedAIDevice.ssid === ""
            ? ""
            : `(${e.selectedAIDevice.ssid}) ${e.selectedAIDevice.user}`;
        p.window.showInformationMessage(
          `Disabled Interactive Terminal Success: ${e.selectedAIDevice.platform} ${e.selectedAIDevice.device} ${h}`
        );
      }
    } else
      !m &&
        v &&
        (e.selectedAIDevice
          ? await (async () => {
              if (!(e.selectedAIDevice instanceof _e)) return;
              (e.selectedAIDevice?.userPort ||
                e.selectedAIDevice.bootMode === I.BootMode.app) &&
                (e.selectedAIDevice?.userPort?.close(G),
                await i.Utils.asyncSleep(1e3)),
                m?.terminal?.dispose(),
                (m = new ee.Interactive("AI Terminal")),
                m.registerCB("Input", (D) => {
                  e.selectedAIDevice instanceof _e &&
                    e.selectedAIDevice.userPort.write(D);
                }),
                e.selectedAIDevice.userPort.registerCallback(
                  "OnRecieveData",
                  (D) => {
                    D !== void 0 && m?.write(D);
                  }
                ),
                m.terminal.show();
              let P = !1,
                y;
              for (
                e.selectedAIDevice?.userPort?.open((D) => {
                  se(D, !1, !1),
                    e.selectedAIDevice instanceof _e &&
                      D &&
                      ((y = new Error(D)), (P = !0));
                });
                !e.selectedAIDevice.userPort.isOpen && !P;

              )
                await i.Utils.asyncSleep(500);
              if (P) throw y;
            })()
              .then(() => {
                if (!(e.selectedAIDevice instanceof _e)) return;
                e.selectedAIDevice.resetTerminal();
                let P =
                  e.selectedAIDevice.ssid === ""
                    ? ""
                    : `(${e.selectedAIDevice.ssid}) ${e.selectedAIDevice.user}`;
                p.window.showInformationMessage(
                  `Enable Interactive Terminal Success: ${e.selectedAIDevice.platform} ${e.selectedAIDevice.device} ${P}`
                );
              })
              .catch(async (P) => {
                p.window.showErrorMessage(
                  `Enable Interactive Terminal Error: ${P.message}`
                ),
                  await p.workspace
                    .getConfiguration()
                    .update(
                      i.Extension.Settings.enableAI3dCameraUserTerminalID,
                      "Disable",
                      p.ConfigurationTarget.Global
                    );
              })
          : ((m = new ee.Interactive("AI Terminal")), m.terminal.show()));
  }
  async function W() {
    if (
      p.workspace
        .getConfiguration()
        .get(
          i.Extension.Settings.enableWebsocketServerID,
          p.ConfigurationTarget.Global
        )
        .toString() === "Enable"
    ) {
      let v = p.workspace
          .getConfiguration()
          .get(i.Extension.Settings.hostNameID, p.ConfigurationTarget.Global)
          .toString(),
        h = p.workspace
          .getConfiguration()
          .get(i.Extension.Settings.portID, p.ConfigurationTarget.Global);
      d.writeLine(
        `VEX Websocket Server Enabled ${v} ${h}`,
        ee.TextColors.green
      ),
        E.start({
          port: h,
          host: v,
        });
    } else
      d.writeLine("VEX Websocket Server Disabled", ee.TextColors.yellow),
        E.stop();
  }
  let V = (u, v = !0) => {
    let h = u.statusCode === 0 ? ee.TextColors.magenta : ee.TextColors.red,
      P =
        u.details === ""
          ? `[Command]: ${u.command}\r
`
          : `[Command]: ${u.command} ${u.details}\r
`,
      y =
        u.details === ""
          ? `[Command]: ${u.command} - (${u.statusCode})`
          : `[Command]: ${u.command} - (${u.statusCode}) ${u.details}`;
    t.appendLine(y),
      u.statusCode !== 0 &&
        v &&
        p.window.showErrorMessage(
          `${u.details} (${u.statusCode}) - ${u.command}`,
          {
            detail: `${u.command}`,
          }
        );
  };
  async function X(u, v = !0) {
    if (!(e.selectedDevice instanceof J)) return;
    let h = "",
      P = ee.TextColors.red;
    if (u)
      u.message.toLowerCase().includes("warning")
        ? ((h = `${u.message}`),
          (P = ee.TextColors.yellow),
          p.window.showWarningMessage(h))
        : ((h = `${
            e.selectedDevice.robotName === ""
              ? `${e.selectedDevice.platform} ${e.selectedDevice.device}`
              : `${e.selectedDevice.platform} ${e.selectedDevice.device} (${e.selectedDevice.robotName})`
          } ${u}`),
          (P = ee.TextColors.red),
          p.window.showErrorMessage(h));
    else {
      let y =
          e.selectedDevice.robotName === ""
            ? `${e.selectedDevice.platform} ${e.selectedDevice.device}`
            : `${e.selectedDevice.platform} ${e.selectedDevice.device} (${e.selectedDevice.robotName})`,
        D =
          e.selectedDevice instanceof Je
            ? e.selectedDevice.communication
            : e.selectedDevice.user;
      (h = `${y} Success: Opening ${D}`),
        (P = ee.TextColors.green),
        v && p.window.showInformationMessage(h);
    }
    (h += `\r
`),
      t.appendLine(h),
      d && d.write(h, P);
  }
  async function ye(u, v) {
    if (!(v instanceof J)) return;
    let h = "",
      P = ee.TextColors.red,
      y =
        v.robotName === ""
          ? `${v.platform} ${v.device}`
          : `${v.platform} ${v.device} (${v.robotName})`;
    if (u && !u?.message.toLowerCase().includes("port is not open"))
      (h = `${y} ${u}`), (P = ee.TextColors.red), p.window.showErrorMessage(h);
    else {
      let D = v instanceof Je ? v.communication : v.user,
        U = `${y} Warning: closed  ${D}`,
        H = ee.TextColors.yellow;
      d?.write(U, H);
    }
    (h += `\r
`),
      t.appendLine(h),
      d && d?.write(h, P);
  }
  async function se(u, v = !0, h = !0) {
    if (!(e.selectedAIDevice instanceof _e)) return;
    let P = "",
      y = ee.TextColors.red;
    u
      ? u.message.toLowerCase().includes("warning")
        ? ((P = `${u.message}`),
          (y = ee.TextColors.yellow),
          p.window.showWarningMessage(P))
        : ((P = `${
            e.selectedAIDevice.ssid === ""
              ? `${e.selectedAIDevice.platform} ${e.selectedAIDevice.device}`
              : `${e.selectedAIDevice.platform} ${e.selectedAIDevice.device} (${e.selectedAIDevice.ssid})`
          } ${u}`),
          (y = ee.TextColors.red),
          h && p.window.showErrorMessage(P))
      : ((P = `${
          e.selectedAIDevice.ssid === ""
            ? `${e.selectedAIDevice.platform} ${e.selectedAIDevice.device}`
            : `${e.selectedAIDevice.platform} ${e.selectedAIDevice.device} (${e.selectedAIDevice.ssid})`
        } Success: Opening ${e.selectedAIDevice.user}`),
        (y = ee.TextColors.green),
        v && p.window.showInformationMessage(P)),
      (P += `\r
`),
      t.appendLine(P),
      m && m.write(P, y);
  }
  async function G(u, v) {
    if (!(v instanceof _e)) return;
    let h = "",
      P = ee.TextColors.red,
      y =
        v.ssid === ""
          ? `${v.platform} ${v.device}`
          : `${v.platform} ${v.device} (${v.ssid})`;
    if (u && !u?.message.toLowerCase().includes("port is not open"))
      (h = `${y} ${u}`), (P = ee.TextColors.red), p.window.showErrorMessage(h);
    else {
      let D = v.user,
        U = `${y} Warning: closed  ${D}`,
        H = ee.TextColors.yellow;
      d?.write(U, H);
    }
    (h += `\r
`),
      t.appendLine(h),
      m && m?.write(h, P);
  }
  async function re(u, v) {
    console.log("Device Manager", e.activeDeviceList),
      u.platform === i.Platform.AI && u.device === i.Device.Camera_3D
        ? i.Extension.Context.isDevEnabled && Uo(u, v)
        : (!e.selectedDevice || v) && le(u, v);
  }
  async function fe(u) {
    console.log("Device Manager", e.activeDeviceList),
      u.platform === i.Platform.AI && u.device === i.Device.Camera_3D
        ? i.Extension.Context.isDevEnabled && yo(u)
        : de(u);
  }
  async function me(u, v) {
    console.log("Device Manager", e.activeDeviceList),
      u.platform === i.Platform.AI && u.device === i.Device.Camera_3D
        ? i.Extension.Context.isDevEnabled && it(u, v)
        : (!e.selectedDevice || v) && _t(u, v);
  }
  async function ue(u) {
    console.log("Device Manager", e.activeDeviceList),
      u.platform === i.Platform.AI && u.device === i.Device.Camera_3D
        ? i.Extension.Context.isDevEnabled && Ut(u)
        : Dt(u);
  }
  async function le(u, v) {
    c.deviceListBtn.show();
    let P =
        p.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.enableUserTerminalID,
            p.ConfigurationTarget.Global
          )
          .toString() === "Enable",
      y,
      D = "",
      U;
    if (((y = ho.createDevice(u)), u.device === i.Device.Brain)) {
      if (((e.selectedDevice = y), !(e.selectedDevice instanceof J))) return;
      v && ((U = await e.selectedDevice.systemInfo()), V(U, !1)),
        o.selectedProject &&
          P &&
          e.selectedDevice.bootMode === I.BootMode.app &&
          e.selectedDevice.userPort.open(X),
        (D = y.vexComSystemInfo.brain.name
          ? `( ${y.vexComSystemInfo.brain.name} )`
          : `( ${y.bootMode} )`),
        e
          .checkSystemVEXOS(y)
          .then((A) => {
            if (e.selectedDevice instanceof J)
              return (
                V(A, !1),
                (e.selectedDevice.needsVexosUpdate = Boolean(A.statusCode)),
                n.refresh(e.selectedDevice, [e.selectedAIDevice]),
                A
              );
          })
          .then(
            (A) => (
              y.json && n.refresh(e.selectedDevice, [e.selectedAIDevice]),
              A.statusCode
                ? p.window.showInformationMessage(A.details, "Update", "Ignore")
                : "Ignore"
            )
          )
          .then((A) => {
            if (A === "Update") return Eo();
          })
          .then((A) => {
            !A ||
              (u.platform === i.Platform.V5 &&
                A.statusCode === x.ExitCode.vexSucess &&
                p.window.showInformationMessage(
                  "VEXos Update Complete: Power Cycle V5 Brain"
                ),
              p.commands.executeCommand(
                "setContext",
                `${i.Extension.id}.vexosBrainUpdateInProgress`,
                !1
              ));
          })
          .catch((A) => {
            p.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexosBrainUpdateInProgress`,
              !1
            );
            let ge = {
              command: "check vexos",
              details: A.message,
              json: "",
              statusCode: -1,
            };
            A.message.includes("Cancel Clicked") ? V(ge, !1) : V(ge);
          });
    } else if (
      u.device === i.Device.Controller &&
      u.platform !== i.Platform.V5
    ) {
      if (((e.selectedDevice = y), !(e.selectedDevice instanceof J))) return;
      v && ((U = await e.selectedDevice.systemInfo()), V(U, !1)),
        o.selectedProject &&
          P &&
          e.selectedDevice.bootMode === I.BootMode.app &&
          e.selectedDevice.userPort.open(X),
        (D = y?.vexComSystemInfo?.brain?.name
          ? `( ${y.vexComSystemInfo.brain.name} )`
          : ""),
        y.platform !== i.Platform.V5 &&
          e
            .checkControllerVEXOS(y)
            .then((A) => {
              if ((V(A, !1), e.selectedDevice)) {
                if (!(e.selectedDevice instanceof J)) return;
                (e.selectedDevice.needsVexosUpdate = Boolean(A.statusCode)),
                  n.refresh(e.selectedDevice, [e.selectedAIDevice]);
              } else return "Ignore";
              return A;
            })
            .then(
              (A) => (
                y.json && n.refresh(e.selectedDevice, [e.selectedAIDevice]),
                A.statusCode
                  ? p.window.showInformationMessage(
                      A.details,
                      "Update",
                      "Ignore"
                    )
                  : "Ignore"
              )
            )
            .then((A) => {
              if (A === "Update") return es();
            })
            .then((A) => {
              p.commands.executeCommand(
                "setContext",
                `${i.Extension.id}.vexosControllerUpdateInProgress`,
                !1
              );
            })
            .catch((A) => {
              p.commands.executeCommand(
                "setContext",
                `${i.Extension.id}.vexosControllerUpdateInProgress`,
                !1
              );
              let ge = {
                command: "check vexos",
                details: A.message,
                json: "",
                statusCode: -1,
              };
              A.message.includes("Cancel Clicked") ? V(ge, !1) : V(ge);
            });
    } else if (
      u.device === i.Device.Controller &&
      u.platform === i.Platform.V5
    ) {
      if (((e.selectedDevice = y), !(e.selectedDevice instanceof J))) return;
      v && ((U = await e.selectedDevice.systemInfo()), V(U, !1)),
        o.selectedProject &&
          P &&
          e.selectedDevice.bootMode === I.BootMode.app &&
          e.selectedDevice.userPort.open(X).then((A) => {
            A.statusCode === x.ExitCode.vexError ? V(A, !1) : V(A);
          }),
        (D = y?.vexComSystemInfo?.brain?.name
          ? `( ${y.vexComSystemInfo.brain.name} )`
          : "");
    }
    y.json && n.refresh(e.selectedDevice, [e.selectedAIDevice]),
      p.window.showInformationMessage(
        `${u.platform} ${u.device} ${D} Connected`
      );
    let H = p.workspace
      .getConfiguration()
      .get(i.Extension.Settings.buildTypeID, p.ConfigurationTarget.Global)
      .toString();
    (c.buildBtn.text = "$(vex-download)"),
      (c.buildBtn.tooltip = `${H} and Download`),
      (c.deviceListBtn.text = `$(vex-${u.platform}-${u.device}) ${D}`),
      !!o.selectedProject &&
        e.selectedDevice instanceof J &&
        (d &&
          d.registerCB("Input", (A) => {
            y.userPort.write(A);
          }),
        e.selectedDevice?.userPort &&
          e.selectedDevice.userPort.registerCallback("OnRecieveData", (A) => {
            A !== void 0 &&
              (E.deviceWSList.length &&
                e.selectedDevice instanceof J &&
                d.write(
                  `${e.selectedDevice.platform} ${e.selectedDevice.device} ( ${e.selectedDevice.robotName} )->`,
                  ee.TextColors.magenta
                ),
              d.write(A),
              E.deviceWSList.forEach((ge) => ge[0].send(A)));
          }));
  }
  async function de(u) {
    if (
      (p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosControllerUpdateInProgress`,
        !1
      ),
      p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosBrainUpdateInProgress`,
        !1
      ),
      e.selectedDevice instanceof J &&
        u.communication === e.selectedDevice.communication)
    ) {
      let v = e.selectedDevice.device,
        h = "";
      if (
        (v === i.Device.Brain
          ? (h = e.selectedDevice.vexComSystemInfo.brain.name
              ? `( ${e.selectedDevice.vexComSystemInfo.brain.name} )`
              : `( ${e.selectedDevice.bootMode} )`)
          : v === i.Device.Controller && (h = ""),
        !(e.selectedDevice instanceof J))
      )
        return;
      if (e.selectedDevice.bootMode === I.BootMode.app) {
        let y = e.selectedDevice;
        e.selectedDevice?.userPort?.close((D) => ye(D, y));
      }
      p.window.showWarningMessage(
        `${u.platform} ${u.device} ${h} Disconnected`
      ),
        (e.selectedDevice = void 0);
      let P = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.buildTypeID, p.ConfigurationTarget.Global)
        .toString();
      if (e.activeDeviceList.length) {
        let y = {
          communication: "",
          bootMode: I.BootMode.unknown,
          user: "",
          device: i.Device.Unknown,
          platform: i.Platform.Unknown,
          robotName: "",
          id: "",
          teamNumber: "",
          json: "",
        };
        if (o?.selectedProject) {
          let D = o.selectedProject.readProjectSettings(),
            U = e.activeDeviceList.filter(
              (H) => D.project.platform === H.platform
            );
          y = U.length >= 1 ? U[0] : e.activeDeviceList[0];
        } else y = e.activeDeviceList[0];
        re(y);
      } else if (e.activeDFUDeviceList.length) {
        let y = {
          bootMode: I.BootMode.dfu,
          device: i.Device.Unknown,
          id: 0,
          pid: "",
          platform: i.Platform.Unknown,
          vid: "",
        };
        if (o?.selectedProject) {
          let D = o.selectedProject.readProjectSettings(),
            U = e.activeDFUDeviceList.filter(
              (H) => D.project.platform === H.platform
            );
          y = U.length >= 1 ? U[0] : e.activeDFUDeviceList[0];
        } else y = e.activeDFUDeviceList[0];
        me(y);
      } else
        (c.deviceListBtn.text = ""),
          c.deviceListBtn.hide(),
          (c.buildBtn.text = "$(vex-build)"),
          (c.buildBtn.tooltip = `${P} User Program`),
          n.clearSD(),
          o.selectedProject || c.deviceListBtn.hide();
    }
  }
  async function _t(u, v) {
    if (!e.selectedDevice || v) {
      if (e.selectedDevice instanceof J) {
        let y = e.selectedDevice;
        if (e.selectedDevice.bootMode === I.BootMode.app) {
          let D = e.selectedDevice;
          e.selectedDevice?.userPort?.close((U) => ye(U, D));
        }
      }
      let h = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.buildTypeID, p.ConfigurationTarget.Global)
        .toString();
      if (
        ((e.selectedDevice = xo.createDevice(u)),
        (c.buildBtn.text = "$(vex-download)"),
        (c.buildBtn.tooltip = `${h} and Download`),
        (c.deviceListBtn.text = `$(vex-${u.platform}-${u.device}) ${u.bootMode}`),
        c.deviceListBtn.show(),
        n.refresh(e.selectedDevice, [e.selectedAIDevice]),
        !(e.selectedDevice instanceof Be) ||
          e.selectedDevice.activeCommand ===
            x.CommandID.controllerRadioUpdate ||
          e.selectedDevice.activeCommand === x.CommandID.controllerUsbUpdate ||
          e.selectedDevice.activeCommand === x.CommandID.recoverDFU)
      )
        return;
      let P = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.dfuAutoRecover, p.ConfigurationTarget.Global);
      ((u.device === i.Device.Brain && P) ||
        (await p.window.showInformationMessage(
          `${u.platform} ${u.device} (DFU) Detected.  Would you like to recover?`,
          "Recover"
        )) === "Recover") &&
        Vo();
    }
  }
  async function Dt(u, v) {
    if (
      u.platform === e.selectedDevice.platform &&
      u.device === e.selectedDevice.device &&
      u.bootMode === e.selectedDevice.bootMode
    ) {
      (e.selectedDevice = void 0),
        n.clearSD(),
        p.window.showWarningMessage(
          `${u.platform} ${u.device} (DFU) Disconnected`
        );
      let h = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.buildTypeID, p.ConfigurationTarget.Global)
        .toString();
      if (e.activeDeviceList.length) {
        let P = {
          communication: "",
          bootMode: I.BootMode.unknown,
          user: "",
          device: i.Device.Unknown,
          platform: i.Platform.Unknown,
          robotName: "",
          id: "",
          teamNumber: "",
          json: "",
        };
        if (o?.selectedProject) {
          let y = o.selectedProject.readProjectSettings(),
            D = e.activeDeviceList.filter(
              (U) => y.project.platform === U.platform
            );
          P = D.length >= 1 ? D[0] : e.activeDeviceList[0];
        } else P = e.activeDeviceList[0];
        re(P, !0);
      } else if (e.activeDFUDeviceList.length) {
        let P = {
          bootMode: I.BootMode.dfu,
          device: i.Device.Unknown,
          id: 0,
          pid: "",
          platform: i.Platform.Unknown,
          vid: "",
        };
        if (o?.selectedProject) {
          let y = o.selectedProject.readProjectSettings(),
            D = e.activeDFUDeviceList.filter(
              (U) => y.project.platform === U.platform
            );
          P = D.length >= 1 ? D[0] : e.activeDFUDeviceList[0];
        } else P = e.activeDFUDeviceList[0];
        me(P, !0);
      } else
        (c.deviceListBtn.text = ""),
          c.deviceListBtn.hide(),
          (c.buildBtn.text = "$(vex-build)"),
          (c.buildBtn.tooltip = `${h} User Program`),
          n.clearSD(),
          o.selectedProject || c.deviceListBtn.hide();
    }
  }
  async function it(u, v) {
    p.window.showInformationMessage(
      `${u.platform} ${u.device} (${u.bootMode}) Detected`
    );
    let h = xo.createDevice(u);
    h instanceof Bt &&
      (console.log(h),
      p.window.showInformationMessage(
        `${u.platform} ${u.device} (${u.bootMode}) Detected`
      ),
      n.refresh(e.selectedDevice, [h]),
      e.selectedAIDevice ||
        ((e.selectedAIDevice = h),
        p.window
          .showInformationMessage(
            "VEX AI 3D Camera Update Available",
            "Update",
            "Ignore"
          )
          .then((P) => {
            P === "Update" &&
              p.commands.executeCommand("vex-sidebar-home-webview.focus");
          })));
  }
  async function Ut(u) {}
  async function Uo(u, v) {
    p.window.showInformationMessage(`${u.platform} ${u.device} Connected`);
    let h = ho.createDevice(u);
    if (!(h instanceof _e)) return;
    let P = h;
    m.writeLine("");
    let y = !1,
      U =
        p.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.enableAI3dCameraUserTerminalID,
            p.ConfigurationTarget.Global
          )
          .toString() === "Enable";
    U &&
      (P.userPort.registerCallback("OnRecieveData", (A) => {
        A && (y = !0), m.write(A);
      }),
      m.registerCB("Input", (A) => {
        P.userPort.serialPort.write(A, (ge) => {
          console.log(ge);
        });
      }),
      P.userPort.open(se)),
      await i.Utils.asyncSleep(2e3);
    let H = !1;
    for (
      P.comsPort.open((A) => {
        H = !0;
      });
      !H;

    )
      await i.Utils.asyncSleep(500);
    if (h instanceof _e) {
      for (let A = 0; A < 3; A++)
        if ((V(await P.checkAlive(), !1), P.isAlive)) {
          let ge = await P.checkElevate();
          V(ge),
            ge.statusCode === F.StatusCodes.nack && V(await P.elevate(), !1),
            V(await P.getDeviceInfo()),
            await e.checkVEXaiApps(P),
            (await e.checkVEXaiVersion(P)).statusCode !== 0 &&
              (h.needsUpdate = !0),
            n.refresh(e.selectedDevice, [P]),
            (A = 3),
            (e.selectedAIDevice = P),
            !y && U && k(!1);
        } else n.refresh(e.selectedDevice, [P]);
      e.selectedAIDevice = P;
    }
  }
  async function yo(u) {
    e.selectedAIDevice instanceof _e &&
      (e.selectedAIDevice.comsPort.serialPort.removeAllListeners(),
      p.window.showWarningMessage(`${u.platform} ${u.device} Disconnected`),
      e.selectedAIDevice.userPort.close(G),
      (e.selectedAIDevice = void 0),
      n.refresh(e.selectedDevice, [e.selectedAIDevice]));
  }
  async function po() {
    t.appendLine("[Command]: Select Python File"),
      o.selectedProject.readProjectSettings().project.language === "python" &&
        c.pickPythonFile(o).then((v) => {
          if (v) {
            c.selectPythonFileBtn.text = v.label;
            let h = o.selectedProject.readProjectSettings();
            (h.project.python.main = v.description),
              o.selectedProject.writeProjectSettings(h),
              t.appendLine(
                `[Command]: Select Python File: Selected ${v.label}`
              ),
              t.appendLine(
                `[Command]: Select Python File: Project Settings ${h}`
              );
          } else
            t.appendLine("[Command]: Select Python File: No File Selected");
        });
  }
  async function K() {
    t.appendLine("[Command]: Select Project");
    let u = await c.selectProject(o);
    if (u) {
      o.selectedProject = u;
      let v = o.selectedProject.readProjectSettings();
      (c.selectSlotBtn.text = `$(vex-slot) Slot ${v.project.slot}`),
        (c.selectProjectBtn.text = `${v.project.name}`),
        t.appendLine(`[Command]: Select Project: Selected ${u.name}`),
        v.project.language === "cpp" &&
          (c.selectProjectBtn.show(), c.selectPythonFileBtn.hide()),
        v.project.language === "python" &&
          (c.selectProjectBtn.show(),
          (c.selectPythonFileBtn.text = `$(python-qp)${zt.basename(
            v.project.python.main
          )}`),
          c.selectPythonFileBtn.show());
    } else t.appendLine("[Command]: Select Project: No Project Selected");
  }
  async function ke() {
    if ((t.appendLine("[Command]: Select Slot"), !o.selectedProject)) {
      t.appendLine(
        "[Command]: Select Slot, No Valid VEX Extension Project Open"
      ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open");
      return;
    }
    c.selectSlot().then((u) => {
      let v = u > 0 && u <= 8 ? `Slot ${u} selected` : "No slot selected";
      if ((t.appendLine(`[Command]: Select Slot: ${v}`), o.selectedProject)) {
        let h = o.selectedProject.readProjectSettings(),
          P = u > 0 && u <= 8 ? u : h.project.slot;
        (h.project.slot = P), o.selectedProject.writeProjectSettings(h);
      }
    });
  }
  async function Te() {
    t.appendLine("[Command]: Download User Program");
    let u = {
      command: i.Extension.Command.downloadID,
      details: "",
      statusCode: -1,
      json: "",
    };
    if (!o.selectedProject)
      return (
        (u.details = "No Valid VEX Extension Project Open"),
        t.appendLine(
          "[Command]: Download User Program, No Valid VEX Extension Project Open"
        ),
        u
      );
    if (!e.selectedDevice)
      return (
        (u.details = "No VEX Device Connected"),
        t.appendLine(
          "[Command]: Download User Program, No VEX Device Connected"
        ),
        u
      );
    if (((u = await To()), u.statusCode !== x.ExitCode.vexSucess)) return u;
    let v = o.selectedProject.readProjectSettings();
    if (e.selectedDevice.platform !== v.project.platform)
      return (
        t.appendLine(`[Command]: Download - Error \r
`),
        t.appendLine(
          `Wrong Platform: Expected ${v.project.platform} Device, ${e.selectedDevice.platform} ${e.selectedDevice.device} connected`
        ),
        {
          command: i.Extension.Command.downloadID,
          details: `Wrong Platform: Expected ${v.project.platform} Device, ${e.selectedDevice.platform} ${e.selectedDevice.device} connected`,
          statusCode: -1,
          json: "",
        }
      );
    let h, P;
    v.project.language === "cpp" &&
      ((h = p.Uri.joinPath(o.selectedProject.projectUri, "build")),
      (P = (await p.workspace.fs.readDirectory(h)).filter((H) =>
        H[0].includes(".bin")
      )[0][0]),
      (h = p.Uri.joinPath(h, P))),
      v.project.language === "python" &&
        (h = p.Uri.joinPath(
          o.selectedProject.projectUri,
          v.project.python.main
        ));
    let y = Boolean(
        p.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.runAfterDownload,
            p.ConfigurationTarget.Global
          )
      ),
      D;
    if (
      e.selectedDevice instanceof vt ||
      e.selectedDevice instanceof Ct ||
      e.selectedDevice instanceof ft
    )
      l.write(`Downloading User Program\r
`),
        (D = await e.selectedDevice.downloadUserProgram(
          v.project.name,
          v.project.description,
          v.project.slot,
          h,
          y
        ));
    else if (e.selectedDevice instanceof et || e.selectedDevice instanceof We)
      l.write(`Downloading User Program\r
`),
        (D = await e.selectedDevice.downloadUserProgram(
          v.project.name,
          v.project.description,
          v.project.slot,
          h,
          y
        ));
    else if (e.selectedDevice instanceof Je) {
      let U = p.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.controllerChannel,
            p.ConfigurationTarget.Global
          )
          .toString(),
        H = x.DownloadChannel.vexNoChannel;
      U === "Download" && e.selectedDevice.device === "Controller"
        ? (H = x.DownloadChannel.vexDownloadchannel)
        : U === "Pit" && (H = x.DownloadChannel.vexPitChannel),
        l.write(`Downloading User Program\r
`),
        (D = await e.selectedDevice.downloadUserProgram(
          v.project.name,
          v.project.description,
          v.project.slot,
          h,
          y,
          H
        ));
    } else
      throw new Error(
        `Download Error: Device Not Recognized ${e.selectedDevice.platform} ${e.selectedDevice.device}`
      );
    return (
      V(D, !1),
      D.statusCode === x.ExitCode.vexAPIErrorFilePath &&
        v.project.language === "python" &&
        po(),
      D
    );
  }
  async function Wo() {
    if (!o.selectedProject) {
      t.appendLine(
        "[Command]: Play Program, No Valid VEX Extension Project Open"
      ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open");
      return;
    }
    let u = o.selectedProject.readProjectSettings();
    if (
      (t.appendLine(`[Command]: Play Slot ${u.project.slot}`),
      !e.selectedDevice)
    ) {
      t.appendLine(
        `[Command]: Play Slot ${u.project.slot}, no device connected`
      );
      return;
    }
    let v = await To();
    if (v.statusCode !== x.ExitCode.vexSucess)
      return (v.command = x.CommandID.play), V(v), v;
    if (!!o.selectedProject && e.selectedDevice instanceof J) {
      if (C) {
        t.appendLine("[Command]: Play Program - Command Dropped");
        return;
      }
      return (
        (C = !0),
        e.selectedDevice
          .play(u.project.slot)
          .then((h) => ((C = !1), V(h), h))
          .catch((h) => {
            C = !1;
            let P = JSON.parse(h.message);
            return V(P), P;
          })
      );
    }
  }
  async function Go() {
    if ((t.appendLine("[Command]: Stop Program"), b)) {
      t.appendLine("[Command]: Stop Program - Command Dropped");
      return;
    }
    if (
      (o.selectedProject ||
        (t.appendLine(
          "[Command]: Stop Program, No Valid VEX Extension Project Open"
        ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open")),
      !e.selectedDevice)
    ) {
      t.appendLine("[Command]: Stop Program, no device connected");
      return;
    }
    let u = await To();
    if (u.statusCode !== x.ExitCode.vexSucess)
      return (u.command = x.CommandID.stop), V(u), u;
    if (e.selectedDevice instanceof J)
      return (
        (b = !0),
        e.selectedDevice
          .stop()
          .then((v) => ((b = !1), V(v), v))
          .catch((v) => {
            b = !1;
            let h = JSON.parse(v.message);
            return V(h), h;
          })
      );
  }
  async function Jo(u) {
    if (!e.selectedDevice) {
      t.appendLine("[Command]: Stop Program, no device connected");
      return;
    }
    if (!J.isTypeOf(e.selectedDevice)) {
      t.appendLine("[Command]: Stop Program, no device connected");
      return;
    }
    let v = await To();
    if (v.statusCode !== x.ExitCode.vexSucess) return V(v), v;
    let h = u,
      P,
      y;
    if (h)
      (y = {
        slot: u.items[0].data,
        file: u.items[1].data,
        projectType: u.items[2].data,
        size: u.items[3].data,
        time: u.items[4].data,
      }),
        (P = u.name.split(":")[1]);
    else {
      if (!(e.selectedDevice instanceof J)) return;
      let D = e.selectedDevice.vexComSystemInfo,
        U = [];
      D.programs &&
        D.programs.items.forEach((A) => {
          U.push({
            label: `$(vex-slot) Slot ${A.slot + 1}`,
            description: `${A.file}.${A.type}`,
          });
        });
      let H = await p.window.showQuickPick(U, {
        placeHolder: "Select a user program to Erase",
        onDidSelectItem: () => {},
      });
      if (H) {
        let A = new RegExp(/(?<=Slot\s*)(1|2|3|4|5|6|7|8)/),
          ge = D.programs.items.filter(
            (to) => `${to.slot + 1}` === A.exec(H.label)[0]
          )[0];
        (y = {
          slot: ge.slot,
          file: ge.binfile,
          projectType: ge.type,
          size: ge.size,
          time: ge.time,
        }),
          (P = ge.file);
      } else return;
    }
    p.window
      .showInformationMessage(
        `Are you sure you want to erase your user program, ${P}?`,
        "Erase",
        "Cancel"
      )
      .then((D) => {
        if (e.selectedDevice instanceof J)
          switch (D) {
            case "Erase":
              t.appendLine(
                `[Command]: Erasing User Program - File: ${y.file} Slot:${y.slot} `
              ),
                e.selectedDevice
                  .erase(y.file)
                  .then((U) => {
                    if (e.selectedDevice instanceof J)
                      return V(U), e.selectedDevice.systemInfo();
                  })
                  .then((U) => {
                    V(U), n.refresh(e.selectedDevice, [e.selectedAIDevice]);
                  })
                  .catch((U) => {
                    let H = JSON.parse(U.message);
                    V(H);
                  });
              break;
          }
      });
  }
  async function qo() {
    if (mo || $t) {
      p.window.showWarningMessage("'List VEX Devices' disabled during update");
      return;
    }
    if (!(e.selectedDevice instanceof J) && !(e.selectedDevice instanceof Be))
      return;
    let u = e.activeDeviceList,
      v = e.activeDFUDeviceList,
      h = !1,
      P = "",
      y = [];
    t.appendLine("[Command]: Select VEX Device"),
      u.length &&
        (u.forEach((U) => {
          let H = "";
          e.selectedDevice instanceof J &&
            ((H = e?.selectedDevice?.communication
              ? e?.selectedDevice?.communication
              : ""),
            (U.robotName !== e.selectedDevice.robotName ||
              U.teamNumber !== e.selectedDevice.teamNumber) &&
              U.communication === e.selectedDevice.communication &&
              U.user === e.selectedDevice.user &&
              e.selectedDevice instanceof J &&
              ((U.communication = e.selectedDevice.communication),
              (U.device = e.selectedDevice.device),
              (U.platform = e.selectedDevice.platform),
              (U.robotName = e.selectedDevice.robotName),
              (U.id = e.selectedDevice.id),
              (U.teamNumber = e.selectedDevice.teamNumber),
              (U.user = e.selectedDevice.user))),
            t.appendLine(`  -${U.platform} ${U.device}:  ${U.robotName} `);
          let A = {
            label: `${U.robotName}`,
            description: `$(vex-${U.platform}-${U.device}) ${U.platform} ${U.device}`,
            detail: `(User):${U.user}   (Comm):${U.communication}`,
          };
          U.communication === H
            ? ((A.label = `$(star-full)${A.label}`), y.unshift(A), (h = !0))
            : y.push(A);
        }),
        (P = "Select VEX Device")),
      v.length &&
        (v.forEach((U) => {
          e.selectedDevice instanceof Be &&
            y.some((A) => U.bootMode === A.label) &&
            U.bootMode !== e.selectedDevice.bootMode &&
            U.vid === e.selectedDevice.vid &&
            U.pid === e.selectedDevice.pid &&
            e.selectedDevice instanceof Be &&
            ((U.bootMode = e.selectedDevice.bootMode),
            (U.vid = e.selectedDevice.pid),
            (U.platform = e.selectedDevice.platform)),
            t.appendLine(`  -${U.platform} ${U.device}:  ${U.bootMode} `);
          let H = {
            label: `${U.bootMode}`,
            description: `$(vex-${U.platform}-${U.device}) ${U.platform} ${U.device}`,
            detail: `(VID):${U.vid}   (PID):${U.pid}`,
          };
          U.bootMode === H.label &&
          H.description.includes(`${U.platform} ${U.device}`) &&
          !h
            ? ((h = !0), (H.label = `$(star-full)${H.label}`), y.unshift(H))
            : y.push(H);
        }),
        (P = "Select VEX Device")),
      !u.length &&
        !v.length &&
        (t.appendLine("[Command]: No Devices Found"),
        (P = "No VEX Devices Found"));
    let D = await p.window.showQuickPick(y, {
      placeHolder: P,
      onDidSelectItem: (U) => {
        U.label.indexOf;
      },
    });
    if (D)
      if (
        (t.appendLine(`[Command]: Selected ${D.label}`),
        e.selectedDevice instanceof J)
      ) {
        let U = u.filter((A) => A.communication === D.detail.split(":")[2])[0],
          H = v.filter((A) => A.bootMode === D.label)[0];
        if (
          e.selectedDevice?.userPort?.isOpen &&
          e.selectedDevice.bootMode === I.BootMode.app
        ) {
          let A = e.selectedDevice;
          e.selectedDevice?.userPort?.close((ge) => ye(ge, A));
        }
        U ? re(U, !0) : H && me(H, !0);
      } else if (e.selectedDevice instanceof Be) {
        let U = u.filter((A) => A.communication === D.detail.split(":")[2])[0],
          H = v.filter((A) => A.bootMode === D.label)[0];
        U
          ? re(U, !0)
          : H &&
            (e.selectedDevice.platform !== U?.platform ||
              e.selectedDevice.device !== U?.device) &&
            me(H, !0);
      } else return;
    return (
      D ||
        (e.selectedDevice || (c.deviceListBtn.text = ""),
        t.appendLine("[Command]: No Device Selected ")),
      D
    );
  }
  async function Ko() {
    let u = "statusBarBuild",
      v = (y, D) => {
        let U = "";
        if ((e.selectedDevice ? (U += "Download") : (U += "Build"), y))
          if (
            (p.window.showErrorMessage(`${U} Failed: ${D || ""}`),
            typeof D == "string")
          ) {
            let H = D?.toString().includes("Vexcom")
              ? D.toString().split(" |")[0]
              : D;
            l.write(
              `${U} Failed: ${D ? H : ""}\r
\r
`,
              ee.TextColors.red
            ),
              t.append(`${U} Failed: ${D || ""}`);
          } else
            l.write(
              `${U} Failed: ${D || ""}\r
\r
`,
              ee.TextColors.red
            ),
              t.append(`

Name:${D.name}
Message:${D.message}
Stack:${D.stack}
`);
        else
          p.window.showInformationMessage(`${U} Finished ${D || ""}`),
            l.write(`${U} Finished ${D || ""}\r
\r
`);
      };
    if ((await p.workspace.saveAll(), o.isBuilding)) return;
    if (e?.selectedDevice && w) {
      t.appendLine("[Command]: Build Sequence In Progress - Command Dropped");
      return;
    }
    w = !0;
    let h = o.selectedProject.readProjectSettings().project.language,
      P;
    switch (h) {
      case "cpp":
        P = async () => Yo();
        break;
      case "python":
        P = async () => Qo();
        break;
      default:
        v(!0, `Language Not Support: ${h}`),
          t.appendLine(`Language Not Support: ${h}`);
        return;
    }
    return P()
      .then((y) => (y?.statusCode === 0 ? v(!1) : v(!0, y.details), y))
      .catch((y) => {
        (w = !1), v(!0, y);
      })
      .finally(() => {
        e.selectedDevice
          ? (c.buildBtn.text = "$(vex-download)")
          : (c.buildBtn.text = "$(vex-build)"),
          (w = !1);
      });
  }
  async function Qo() {
    if (
      (t.appendLine(""),
      t.appendLine("Python Build Btn Sequence"),
      (c.buildBtn.text = "$(loading~spin)Downloading..."),
      !e.selectedDevice)
    ) {
      t.appendLine("No Device connected, so python file can't be downloaded"),
        l.write(`No Device connected, so python file can't be downloaded\r
`);
      let h = {
        command: Me.buildCmdId,
        details: "No device connected",
        statusCode: 0,
        json: "",
      };
      return (
        p.window.showWarningMessage(
          "No Device connected, so python file can't be downloaded"
        ),
        h
      );
    }
    await i.Extension.Command.systemUpdatePythonVM(!1);
    let u = await i.Extension.Command.downloadUserProgram();
    return u.statusCode !== 0
      ? u
      : {
          command: Me.buildCmdId,
          details: "Python Build Sequence Success",
          statusCode: 0,
          json: "",
        };
  }
  async function Yo() {
    t.appendLine(""),
      t.appendLine("CPP Build"),
      (c.buildBtn.text = "$(loading~spin)Building...");
    let u = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.buildTypeID, p.ConfigurationTarget.Global)
        .toString(),
      v;
    u === "Rebuild"
      ? (v = async () => i.Extension.Command.rebuild())
      : (v = async () => i.Extension.Command.build());
    let h = await v();
    if (h !== 0 || !e.selectedDevice)
      return {
        command: `${i.Extension.id}.project.${String(u).toLowerCase()}`,
        details:
          h < 0
            ? `${Ke.getErrorMessageFromCode(h)}`
            : `Make process closed with exit code: ${h}`,
        statusCode: h,
        json: "",
      };
    c.buildBtn.text = "$(loading~spin)Downloading...";
    let P = await i.Extension.Command.downloadUserProgram();
    return P.statusCode !== 0
      ? P
      : e.selectedDevice instanceof J
      ? (n.refresh(e.selectedDevice, [e.selectedAIDevice]),
        {
          command: Me.buildCmdId,
          details: `C++ ${u} Sequence Success`,
          statusCode: 0,
          json: "",
        })
      : void 0;
  }
  async function he(u) {
    if (
      (console.log(u),
      t.appendLine(""),
      t.appendLine("[Command]: Build Project"),
      !o.selectedProject)
    ) {
      t.appendLine(
        "[Command]: Build Project, No Valid VEX Extension Project Open"
      ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open");
      return;
    }
    if (o.selectedProject.language !== i.Language.cpp) {
      p.window.showWarningMessage("Build is only avaliable for C++ Projects");
      return;
    }
    let v = await o
      .build()
      .then((h) => (l.write(""), h))
      .catch(
        (h) => (
          p.window.showErrorMessage(`Build Failed - ${h}`),
          t.appendLine(`[Command]: Build ${h}`),
          h
        )
      );
    if (!u) return v;
  }
  async function De(u) {
    if (
      (t.appendLine(""),
      t.appendLine("[Command]: Clean Project"),
      !o.selectedProject)
    ) {
      t.appendLine(
        "[Command]: Clean Project, No Valid VEX Extension Project Open"
      ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open");
      return;
    }
    if (o.selectedProject.language !== i.Language.cpp) {
      p.window.showWarningMessage("Clean is only avaliable for C++ Projects");
      return;
    }
    let v = o
      .clean()
      .then(
        (h) => (
          p.window.showInformationMessage("Clean Project Finshed"),
          t.appendLine(`[Command]: Clean Project Finished: Exit Code ${h}`),
          h
        )
      )
      .catch(
        (h) => (
          p.window.showErrorMessage(`Clean Project Failed - ${h}`),
          t.appendLine(`[Command]: Clean Project Error: ${h}`),
          h
        )
      );
    if (!u) return v;
  }
  async function Le(u) {
    if (
      (t.appendLine(""),
      t.appendLine("[Command]: Rebuild Project"),
      !o.selectedProject)
    ) {
      t.appendLine(
        "[Command]: Rebuild Project, No Valid VEX Extension Project Open"
      ),
        p.window.showWarningMessage("No Valid VEX Extension Project Open");
      return;
    }
    if (o.selectedProject.language !== i.Language.cpp) {
      p.window.showWarningMessage("Rebuild is only avaliable for C++ Projects");
      return;
    }
    let v = o
      .rebuild()
      .then(
        (h) => (
          h === void 0 || h !== 0
            ? (p.window.showErrorMessage(
                `Rebuild Failed: make process closed with exit code : ${h}`
              ),
              t.appendLine(
                `[Command]: Rebuild Failed: make process closed with exit code : ${h}`
              ))
            : t.appendLine(`[Command]: Rebuild Finished: Exit Code ${h}`),
          h
        )
      )
      .catch(
        (h) => (
          p.window.showErrorMessage("Error: Rebuild Project Failed"),
          p.window.showErrorMessage(`Rebuild Project Failed - ${h}`),
          t.appendLine(`[Command]: Rebuild Project ${h}`),
          h
        )
      );
    if (!u) return v;
  }
  async function Wt() {
    t.appendLine("[Command]: New Project"),
      o
        .newProject()
        .then((u) => {
          u
            ? t.appendLine(`[Command]:${u}`)
            : t.appendLine("[Command]: New Project Finished");
        })
        .catch((u) => {
          l.write(
            `${u}\r
`,
            ee.TextColors.red
          ),
            t.appendLine(`[Command]: New Project ${u}\r
`);
        });
  }
  async function So() {
    t.appendLine("Import Project"),
      o
        .importProject()
        .then((u) => {
          t.appendLine(`Import Project Finshed: ${u}`);
        })
        .catch((u) => {
          t.appendLine(`[Command]: Import Project Failed: ${u}\r
`),
            p.window.showErrorMessage(`Import Project Failed: ${u.message}`);
        });
  }
  async function vs() {
    if (!o.selectedProject) {
      p.window.showErrorMessage("No Project Found");
      return;
    }
    t.appendLine("[Command]: Show Project Settings UI "),
      o
        .showSettingsUI()
        .then(() => {
          t.appendLine("[Command]: Show Project Settings UI Finished "),
            (c.selectProjectBtn.text = o.selectedProject.name);
        })
        .catch((u) => {
          t.appendLine(`[Command]: Show Project Settings Error: ${u}\r
`),
            p.window.showErrorMessage(`Project Settings Invalid:${u.message}`),
            lt.Reset();
        });
  }
  async function fs() {
    let u;
    ze.type() === "Windows_NT"
      ? (u = p.Uri.joinPath(p.Uri.file(process.env.USERPROFILE), "Documents"))
      : ze.type() === "Darwin"
      ? (u = p.Uri.joinPath(p.Uri.file(process.env.HOME), "Documents"))
      : ze.type() === "Linux" &&
        (u = p.Uri.joinPath(p.Uri.file(process.env.HOME), "Documents"));
    let h = {
      defaultUri: o.selectedProject ? o.selectedProject.projectUri : u,
      filters: {
        png: ["png"],
      },
    };
    p.window.showSaveDialog(h).then((P) => {
      e.selectedDevice instanceof J &&
        P !== void 0 &&
        e.selectedDevice
          .screenGrab(P)
          .then((y) => {
            V(y),
              y.statusCode === 0 && p.commands.executeCommand("vscode.open", P);
          })
          .catch((y) => {
            let D = JSON.parse(y.message);
            V(D);
          });
    });
  }
  async function hs() {
    let u;
    ze.type() === "Windows_NT"
      ? (u = p.Uri.joinPath(p.Uri.file(process.env.USERPROFILE), "Documents"))
      : ze.type() === "Darwin"
      ? (u = p.Uri.joinPath(p.Uri.file(process.env.HOME), "Documents"))
      : ze.type() === "Linux" &&
        (u = p.Uri.joinPath(p.Uri.file(process.env.HOME), "Documents"));
    let h = {
        defaultUri: o.selectedProject ? o.selectedProject.projectUri : u,
        filters: {
          vexlog: ["vexlog"],
          txt: ["txt"],
        },
      },
      P = await p.window.showSaveDialog(h);
    if (!(e.selectedDevice instanceof J) || P === void 0) return;
    let y = Number(
      p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.logEntriesID, p.ConfigurationTarget.Global)
    );
    e.selectedDevice
      .uploadEventLog(y)
      .then(async (D) => {
        if ((V(D), D.statusCode === 0)) {
          i.Utils.isJsonString(D.json) ||
            (await p.workspace.fs.writeFile(
              P,
              new TextEncoder().encode(D.json)
            ),
            await p.commands.executeCommand("vscode.open", P));
          let H = JSON.parse(D.json),
            A = "";
          H.log.items.forEach((q) => {
            A += `${q.time} (${q.type}) ${q.description}${ze.EOL}`;
          }),
            await p.workspace.fs.writeFile(P, new TextEncoder().encode(A));
          let ge = new p.Position(H.log.count - 1, 0),
            to = await p.workspace.openTextDocument(P),
            Qe = await p.window.showTextDocument(to);
          Qe.selections = [new p.Selection(ge, ge)];
          var U = new p.Range(ge, ge);
          Qe.revealRange(U);
        }
      })
      .catch((D) => {
        let U = JSON.parse(D.message);
        V(U);
      });
  }
  async function xs() {
    if (e.selectedDevice.platform !== "V5") {
      p.window.showWarningMessage(
        "Battery Medic is only avaliable to VEX V5 Devices"
      );
      return;
    }
    e.selectedDevice instanceof J &&
      e.selectedDevice
        .batteryMedic()
        .then((u) => {
          V(u);
        })
        .catch((u) => {});
  }
  async function kt() {
    if (!(e.selectedDevice instanceof J)) return;
    let u = await e.selectedDevice.systemInfo();
    if (
      (V(u, !1),
      u.statusCode !== -7 && n.refresh(e.selectedDevice, [e.selectedAIDevice]),
      u.statusCode === x.ExitCode.vexSucess &&
        !c?.deviceListBtn?.text.includes(e.selectedDevice.robotName))
    ) {
      let v = "";
      e.selectedDevice.device === "Brain"
        ? (v = e.selectedDevice.robotName
            ? `( ${e.selectedDevice.robotName} )`
            : `( ${e.selectedDevice.robotName} )`)
        : e.selectedDevice.device === "Controller" &&
          (v = e.selectedDevice.robotName
            ? `( ${e.selectedDevice.robotName} )`
            : ""),
        (c.deviceListBtn.text = `$(vex-${e.selectedDevice.platform}-${e.selectedDevice.device})  ${v}`);
    }
  }
  async function bs() {
    let v = {
      placeHolder: "Type brain name here . . .",
      validateInput: (H) =>
        H.length > 8
          ? "Name To Long"
          : /[ `!@#$%^&*()+\=\[\]{};':"\\|,.<>\/?~]/.test(H)
          ? "Special Charaters not allowed"
          : null,
      title: "Set Brain Name",
    };
    if (!(e.selectedDevice instanceof J)) return;
    let P = await (async () => p.window.showInputBox(v))();
    if (!P) throw new Error("No Brain Name Entered");
    let y = await e.selectedDevice.setRobotName(P);
    V(y), (y = await e.selectedDevice.systemInfo());
    let D = JSON.parse(y.json),
      U;
    D.iq2 && e.selectedDevice.platform === "IQ2" && (U = D.iq2),
      D.exp && e.selectedDevice.platform === "EXP" && (U = D.exp),
      D.v5 && e.selectedDevice.platform === "V5" && (U = D.v5),
      (c.deviceListBtn.text = `$(vex-${e.selectedDevice.platform}-${e.selectedDevice.device})  ${e.selectedDevice.robotName}`),
      V(y),
      n.refresh(e.selectedDevice, [e.selectedAIDevice]);
  }
  async function ws() {
    let v = {
      placeHolder: "Type team number here . . .",
      validateInput: (D) =>
        D.length > 8
          ? "Team Number To Long"
          : /[ `!@#$%^&*()+\=\[\]{};':"\\|,.<>\/?~]/.test(D)
          ? "Special Charaters not allowed"
          : null,
      title: "Set Team Number",
    };
    if (!(e.selectedDevice instanceof J)) return;
    let P = await (async () => p.window.showInputBox(v))();
    if (!P) throw new Error("No Team Number Entered");
    let y = await e.selectedDevice.setTeamName(P);
    V(y),
      (y = await e.selectedDevice.systemInfo()),
      V(y),
      n.refresh(e.selectedDevice, [e.selectedAIDevice]);
  }
  async function Cs() {
    let u = p.Uri.joinPath(_.globalStorageUri, "vexos"),
      v = p.Uri.joinPath(u, i.Platform.EXP),
      h = p.Uri.joinPath(u, i.Platform.IQ2),
      P = p.Uri.joinPath(u, i.Platform.V5),
      y = JSON.parse(
        (await i.Extension.ResourceManager.getVEXosVersions(i.Platform.EXP, u))
          .json
      ),
      D = JSON.parse(
        (await i.Extension.ResourceManager.getVEXosVersions(i.Platform.IQ2, u))
          .json
      ),
      U = JSON.parse(
        (await i.Extension.ResourceManager.getVEXosVersions(i.Platform.V5, u))
          .json
      );
    t.appendLine(`V5:  ${JSON.stringify(U)}`),
      t.appendLine(`IQ2: ${JSON.stringify(D)}`),
      t.appendLine(`EXP: ${JSON.stringify(y)}`),
      y.online.latest > y.local.latest || !y.local.catalog.length
        ? i.Extension.ResourceManager.downloadLatestVEXos(i.Platform.EXP, v)
        : t.appendLine("EXP: Latest vexos file available locally"),
      D.online.latest > D.local.latest || !D.local.catalog.length
        ? i.Extension.ResourceManager.downloadLatestVEXos(i.Platform.IQ2, h)
        : t.appendLine("IQ2: Latest vexos file available locally"),
      U.online.latest > U.local.latest || !U.local.catalog.length
        ? i.Extension.ResourceManager.downloadLatestVEXos(i.Platform.V5, P)
        : t.appendLine("V5: Latest vexos file available locally");
  }
  async function fi() {
    let u = p.workspace
        .getConfiguration()
        .get(i.Extension.Settings.aiCameraHomeID, p.ConfigurationTarget.Global)
        .toString(),
      v = p.Uri.file(u),
      h = JSON.parse(
        (await i.Extension.ResourceManager.getVEXaiAppListVersions(v)).json
      );
    t.appendLine(`VEXai 3D Camera App Versions: ${JSON.stringify(h)}`);
    let P = [];
    await h.online.apps.forEach(async (y) => {
      let D = await i.Extension.ResourceManager.getVEXaiAppVersions(y, v),
        U = JSON.parse(D.json);
      U.online.latest > U.local.latest || !U.local.catalog.length
        ? await i.Extension.ResourceManager.downloadVEXaiApp(U.online.latest)
        : t.appendLine(`VEXai: Latest ${y} available locally`);
    }),
      console.log("finished loop "),
      console.log(P);
  }
  async function Zo() {
    if (!(e.selectedAIDevice instanceof _e)) return;
    let u = await e.selectedAIDevice.getDeviceInfo();
    V(u, !1),
      u.statusCode !== -7 && n.refresh(e.selectedDevice, [e.selectedAIDevice]);
  }
  let mo = !1;
  async function Eo() {
    if (
      !(
        e.selectedDevice instanceof ft ||
        e.selectedDevice instanceof vt ||
        e.selectedDevice instanceof Ct ||
        e.selectedDevice instanceof Je
      )
    )
      return;
    if (e.selectedDevice instanceof Je) {
      let v = await p.window.showInformationMessage(
        "VEXos System Update",
        {
          detail:
            "Would you like to update VEXos through a V5 Controller?  V5 Controller must be tethered to a V5 brain. VEXos update will take serval minutes to complete.  DO NOT UNPLUG during VEXos update.",
          modal: !0,
        },
        "Update"
      );
      if ((console.log(v), v !== "Update")) return;
    }
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    (mo = !0),
      p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosBrainUpdateInProgress`,
        !0
      ),
      (async () => {
        if (
          !(
            e.selectedDevice instanceof ft ||
            e.selectedDevice instanceof vt ||
            e.selectedDevice instanceof Ct ||
            e.selectedDevice instanceof Je
          )
        )
          return;
        let v = e.selectedDevice.platform,
          h = p.Uri.joinPath(_.globalStorageUri, "vexos"),
          P = (await i.Extension.ResourceManager.getVEXosVersions(v, h)).json,
          y = JSON.parse(P),
          D = p.Uri.joinPath(h, v, y.local.latest + ".vexos");
        y.local.catalog.includes(y.online.latest) ||
          (await i.Extension.ResourceManager.downloadLatestVEXos(
            v,
            p.Uri.joinPath(h, v)
          ),
          (P = (await i.Extension.ResourceManager.getVEXosVersions(v, h)).json),
          (y = JSON.parse(P)),
          (D = p.Uri.joinPath(h, v, y.local.latest + ".vexos")));
        let U = await e.selectedDevice.systemUpdate(D, !0);
        return (
          U.statusCode === x.ExitCode.vexSucess &&
            e.selectedDevice &&
            (e.selectedDevice.needsVexosUpdate = !1),
          V(U),
          kt(),
          U
        );
      })()
        .then(
          (v) => (
            (mo = !1),
            p.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexosBrainUpdateInProgress`,
              !1
            ),
            ($t = !1),
            v
          )
        )
        .catch((v) => {
          throw (
            ((mo = !1),
            ($t = !1),
            p.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexosBrainUpdateInProgress`,
              !1
            ),
            new Error(v.message))
          );
        });
  }
  let $t = !1;
  async function es(u, v) {
    if ($t) {
      p.window.showWarningMessage("Controller Update In Progress");
      return;
    }
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    if (
      (e.selectedDevice.platform !== i.Platform.EXP &&
        e.selectedDevice.platform !== i.Platform.IQ2) ||
      e.selectedDevice.device !== i.Device.Controller
    ) {
      p.window.showWarningMessage(
        `Controller updates not allowed for: ${e.selectedDevice.platform} ${e.selectedDevice.device}`
      );
      return;
    }
    return (
      ($t = !0),
      p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosControllerUpdateInProgress`,
        !0
      ),
      (async () => {
        if (!(e.selectedDevice instanceof We || e.selectedDevice instanceof et))
          return;
        let P = {
          command: "",
          details: "",
          json: "",
          statusCode: 0,
        };
        if (
          e.selectedDevice.needsRadioUpdate ||
          e.selectedDevice.needsUsbUpdate
        ) {
          let y = e.selectedDevice.platform,
            D = p.Uri.joinPath(_.globalStorageUri, "vexos"),
            U = (await i.Extension.ResourceManager.getVEXosVersions(y, D)).json,
            H = JSON.parse(U),
            A = p.Uri.joinPath(D, y, H.local.latest + ".vexos");
          H.local.catalog.includes(H.online.latest) ||
            (await i.Extension.ResourceManager.downloadLatestVEXos(
              y,
              p.Uri.joinPath(D, y)
            ),
            (U = (await i.Extension.ResourceManager.getVEXosVersions(y, D))
              .json),
            (H = JSON.parse(U)),
            (A = p.Uri.joinPath(D, y, H.local.latest + ".vexos"))),
            e.selectedDevice.needsRadioUpdate && e.selectedDevice.needsUsbUpdate
              ? ((P = await e.selectedDevice.controllerUpdate(A)), V(P, !1))
              : e.selectedDevice.needsRadioUpdate
              ? ((P = await e.selectedDevice.controllerRadioUpdate(A)),
                kt(),
                V(P, !1))
              : e.selectedDevice.needsUsbUpdate &&
                ((P = await e.selectedDevice.controllerUsbUpdate(A)), V(P, !1)),
            P.statusCode === x.ExitCode.vexSucess
              ? (e?.selectedDevice && (e.selectedDevice.needsRadioUpdate = !1),
                p.window.showInformationMessage(
                  `${y} Controller Update: Success`
                ))
              : p.window.showErrorMessage(`${y} Controller Update: Failed`);
        } else
          p.window.showInformationMessage(
            `No update needed, ${e.selectedDevice.platform} ${e.selectedDevice.device} up to date!`
          );
        return P;
      })()
        .then(
          (P) => (
            p.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexosControllerUpdateInProgress`,
              !1
            ),
            ($t = !1),
            P
          )
        )
        .catch((P) => {
          throw (
            (($t = !1),
            p.commands.executeCommand(
              "setContext",
              `${i.Extension.id}.vexosControllerUpdateInProgress`,
              !1
            ),
            new Error(P.message))
          );
        })
    );
  }
  async function hi() {
    if (!(e.selectedDevice instanceof We)) return;
    let u = e.selectedDevice.platform,
      v = p.Uri.joinPath(_.globalStorageUri, "vexos"),
      h = (await i.Extension.ResourceManager.getVEXosVersions(u, v)).json,
      P = JSON.parse(h),
      y = p.Uri.joinPath(v, u, P.local.latest + ".vexos");
    P.local.catalog.includes(P.online.latest) ||
      (await i.Extension.ResourceManager.downloadLatestVEXos(
        u,
        p.Uri.joinPath(v, u)
      ),
      (h = (await i.Extension.ResourceManager.getVEXosVersions(u, v)).json),
      (P = JSON.parse(h)),
      (y = p.Uri.joinPath(v, u, P.local.latest + ".vexos")));
    let D = await e.selectedDevice.controllerUsbUpdate(y);
    return (
      D.statusCode === x.ExitCode.vexSucess &&
        e.selectedDevice &&
        (e.selectedDevice.needsVexosUpdate = !1),
      V(D),
      kt(),
      D
    );
  }
  async function xi() {
    if (!(e.selectedDevice instanceof We)) return;
    let u = e.selectedDevice.platform,
      v = p.Uri.joinPath(_.globalStorageUri, "vexos"),
      h = (await i.Extension.ResourceManager.getVEXosVersions(u, v)).json,
      P = JSON.parse(h),
      y = p.Uri.joinPath(v, u, P.local.latest + ".vexos");
    P.local.catalog.includes(P.online.latest) ||
      (await i.Extension.ResourceManager.downloadLatestVEXos(
        u,
        p.Uri.joinPath(v, u)
      ),
      (h = (await i.Extension.ResourceManager.getVEXosVersions(u, v)).json),
      (P = JSON.parse(h)),
      (y = p.Uri.joinPath(v, u, P.local.latest + ".vexos")));
    let D = await e.selectedDevice.controllerRadioUpdate(y);
    return (
      D.statusCode === x.ExitCode.vexSucess &&
        e.selectedDevice &&
        (e.selectedDevice.needsVexosUpdate = !1),
      V(D),
      kt(),
      D
    );
  }
  async function Is(u) {
    o.selectedProject ||
      p.window.showErrorMessage("No Valid VEX Extension Project Open");
    let v = p.window.activeTextEditor;
    if (!v) return;
    let h = v.selection.start,
      P = new p.Range(v.selection.start, v.selection.end);
    if ((v.document.lineAt(v.selection.active.line).text, !o.selectedProject))
      return;
    let y = o.selectedProject.readProjectSettings(),
      D = await r.getActiveList(y.project.platform, y.project.language),
      U = v.document.lineAt(v.selection.active.line).text,
      H = v.document.getText(P),
      A = new RegExp(`(?<=s*)${H}(?=.w*.w*)`),
      ge = new RegExp(`(?<=s*.w*)${H}(?=.w*)`),
      to = new RegExp(`(?<=s*.w*.w)${H}`),
      Qe = "";
    Qe.includes(".") ? (Qe = H.split(".").join("_")) : (Qe = H);
    let q = D.filter(
      (Y) =>
        Y.name.toLowerCase().includes(Qe.toLowerCase()) ||
        Y.signature.toLowerCase().includes(Qe.toLowerCase())
    );
    if (q.length === 0) {
      await ts(u);
      return;
    } else if (q.length === 1) r.Show(q[0]);
    else {
      let Y = [];
      q.forEach((pe) => {
        if (pe.signature.includes("_")) {
          let ve = pe.name.split("_"),
            mt = ve.shift(),
            yt = ve.join("_");
          Y.push({
            label: pe.signature,
            description: pe.category,
          });
        } else {
          let ve = pe.category,
            mt = pe.signature;
          Y.push({
            label: pe.signature,
            description: pe.category,
          });
        }
      });
      let Oe = await p.window.showQuickPick(Y, {
        canPickMany: !1,
        title: "VEX Command Help",
        placeHolder: "Select Command",
      });
      if (!Oe) return;
      if (Oe.label.includes(":")) {
        let pe = Oe.label.replace(": ", "_"),
          ve = D.filter((yt) => yt.name === pe)[0],
          mt = D.filter((yt) => yt.signature === Oe.label)[0];
        if (ve) {
          r.Show(ve);
          return;
        } else
          mt
            ? r.Show(mt)
            : p.window.showErrorMessage(
                `VEX Command Help Error: ${Oe.label} not found`
              );
      } else {
        let pe = D.filter((ve) => ve.signature === Oe.label)[0];
        r.Show(pe);
      }
    }
  }
  async function ts(u) {
    if (!o.selectedProject) return;
    let v = o.selectedProject.readProjectSettings(),
      h = await r.getActiveList(v.project.platform, v.project.language),
      P = [],
      y = [];
    h.forEach((U) => {
      if (U.signature.includes("_")) {
        let H = U.name.split("_"),
          A = H.shift(),
          ge = H.join("_");
        y.push({
          label: U.signature,
          description: U.category,
        });
      } else {
        let H = U.category,
          A = U.signature;
        y.push({
          label: U.signature,
          description: U.category,
        });
      }
    });
    let D = await p.window.showQuickPick(y, {
      canPickMany: !1,
      title: "Vex Command Help",
      placeHolder: "Select Command",
    });
    if (!!D)
      if (D.label.includes(":")) {
        let U = D.label.replace(": ", "_"),
          H = h.filter((A) => A.name === U)[0];
        r.Show(H);
      } else {
        let U = h.filter((H) => H.signature === D.label)[0];
        r.Show(U);
      }
  }
  async function Ps(u) {
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    if (!(e.selectedDevice instanceof J)) return;
    if (
      (e.selectedDevice instanceof Je && V(await e.selectedDevice.systemInfo()),
      !o.selectedProject)
    ) {
      V(await e.selectedDevice.downloadPythonVM(), !0);
      return;
    }
    n.refresh(e.selectedDevice, [e.selectedAIDevice]);
    let v = JSON.parse(e.selectedDevice.json),
      h = o.selectedProject.readProjectSettings(),
      P = v.v5 ? v.v5 : v.iq2 || v.iq2 ? v.iq2 : v.exp,
      y = p.Uri.file(
        p.workspace
          .getConfiguration()
          .get(
            i.Extension.Settings.sdkPythonHomeID,
            p.ConfigurationTarget.Global
          )
          .toString()
      );
    if (
      h.project.platform === e.selectedDevice.platform &&
      e.selectedDevice.bootMode === I.BootMode.app &&
      h.project.language === i.Language.python &&
      P?.brain
    ) {
      let D = p.Uri.joinPath(
          y,
          h.project.platform,
          h.project.sdkVersion,
          `vex${h.project.platform.toLowerCase()}`,
          "vm",
          "python_vm.bin"
        ),
        U = h.project.sdkVersion,
        H = `${h.project.platform.toUpperCase()}_${i.Utils.vexos
          .toVersion(P.vms?.items[0]?.version)
          .split(".")
          .join("_")}`,
        A = `${h.project.platform.toUpperCase()}_${i.Utils.vexos
          .toVersion(v.files.python_vm.version)
          .split(".")
          .join("_")}`;
      if (!P?.vms.count) V(await e.selectedDevice.downloadPythonVM(D));
      else if (U > H) V(await e.selectedDevice.downloadPythonVM(D));
      else if (A > H) V(await e.selectedDevice.downloadPythonVM());
      else if (u && D) V(await e.selectedDevice.downloadPythonVM(D));
      else if (u) V(await e.selectedDevice.downloadPythonVM());
      else return;
    } else u === void 0 && V(await e.selectedDevice.downloadPythonVM(), !0);
  }
  async function _s() {
    if (o.selectedProject) {
      let u = "",
        v = o.selectedProject.readProjectSettings(),
        h = o.getSDKHomeUriFromLanguage(v.project.language);
      h
        ? i.Extension.ResourceManager.downloadSDK(
            v.project.platform,
            v.project.language,
            v.project.sdkVersion,
            h
          )
        : p.window.showErrorMessage(`${v.project.language} Language not valid`);
    } else
      p.window.showWarningMessage(
        "Valid Project must be opened to download SDK"
      );
  }
  async function Ds() {
    let u = [i.Platform.V5, i.Platform.EXP, i.Platform.IQ2],
      v = [i.Language.cpp, i.Language.python];
    for (let h = 0; h < u.length; h++) {
      let P = u[h];
      for (let y = 0; y < v.length; y++) {
        let D = v[y],
          U = p.Uri.joinPath(i.Extension.context.globalStorageUri, "sdk", D),
          H = await i.Extension.ResourceManager.getSDKVersion(P, D, U),
          A = JSON.parse(H.json);
        if (D === i.Language.python) {
          let ge = A.online.latest.split("_").slice(0, 5).join("_");
          console.log(ge),
            A.local.latest !== ge &&
              A.online.latest !== "" &&
              V(
                await i.Extension.ResourceManager.downloadSDK(
                  P,
                  D,
                  A.online.latest,
                  U
                ),
                !1
              );
        } else
          D === i.Language.cpp
            ? A.local.latest !==
                A.online.latest.split("_").slice(0, 5).join("_") &&
              A.online.latest !== "" &&
              V(
                await i.Extension.ResourceManager.downloadSDK(
                  P,
                  D,
                  A.online.latest,
                  U
                ),
                !1
              )
            : A.local.latest !== A.online.latest &&
              A.online.latest !== "" &&
              V(
                await i.Extension.ResourceManager.downloadSDK(
                  P,
                  D,
                  A.online.latest,
                  U
                ),
                !1
              );
        A.local.latest !== "" && console.log(A);
      }
    }
  }
  async function Q(u) {
    i.Extension.ResourceManager.downloadToolchain();
  }
  async function os() {
    l?.clear(), ee.Log.clearTempLog();
  }
  async function bi() {
    d?.clear();
  }
  async function wi() {
    l && l.terminal.dispose(),
      d && d.terminal.dispose(),
      (l = new ee.Log()),
      (d = new ee.Interactive("Interactive Terminal", l.terminal)),
      l.terminal.show();
  }
  async function Vo() {
    if (e.selectedDevice instanceof Ot || e.selectedDevice instanceof Lt) {
      p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosBrainUpdateInProgress`,
        !0
      ),
        p.window.showInformationMessage("");
      let u = await e.selectedDevice.recover();
      V(u),
        u.statusCode === x.ExitCode.vexSucess &&
          p.window.showInformationMessage(
            `${e.selectedDevice.platform} ${e.selectedDevice.device} DFU Recover Success`
          ),
        p.commands.executeCommand(
          "setContext",
          `${i.Extension.id}.vexosBrainUpdateInProgress`,
          !1
        );
    }
    if (e.selectedDevice instanceof Et || e.selectedDevice instanceof St) {
      let u = p.Uri.joinPath(_.globalStorageUri, "vexos"),
        v = (
          await i.Extension.ResourceManager.getVEXosVersions(
            e.selectedDevice.platform,
            u
          )
        ).json,
        h = JSON.parse(v),
        P = p.Uri.joinPath(
          u,
          e.selectedDevice.platform,
          h.local.latest + ".vexos"
        );
      !h.local.catalog.includes(h.online.latest) &&
        h.latest !== "" &&
        (await i.Extension.ResourceManager.downloadLatestVEXos(
          e.selectedDevice.platform,
          p.Uri.joinPath(u, e.selectedDevice.platform)
        ),
        (v = (
          await i.Extension.ResourceManager.getVEXosVersions(
            e.selectedDevice.platform,
            u
          )
        ).json),
        (h = JSON.parse(v)),
        (P = p.Uri.joinPath(
          u,
          e.selectedDevice.platform,
          h.local.latest + ".vexos"
        ))),
        p.commands.executeCommand(
          "setContext",
          `${i.Extension.id}.vexosControllerUpdateInProgress`,
          !0
        );
      let y = await e.selectedDevice.controllerUsbUpdate(P),
        D = 3e3,
        U = 0,
        H = 100,
        A = e.selectedDevice;
      for (
        ;
        U < D &&
        (await i.Utils.asyncSleep(H),
        (U += H),
        !(!e.selectedDevice || e?.selectedDevice?.bootMode !== I.BootMode.dfu));

      );
      if (
        y.statusCode === x.ExitCode.vexSucess &&
        e?.selectedDevice?.bootMode !== I.BootMode.dfu
      )
        V(y),
          p.window.showInformationMessage(
            `${A.platform} ${A.device} DFU Recover Success`
          );
      else {
        p.window.showErrorMessage(
          `${A.platform} ${A.device} DFU Recover Failed`
        );
        let ge = await Us(!1);
      }
      p.commands.executeCommand(
        "setContext",
        `${i.Extension.id}.vexosControllerUpdateInProgress`,
        !1
      );
    }
  }
  async function Us(u = !0) {
    let v = {
      command: i.Extension.Command.installDrivers,
      details: "Driver Install Only Avaliable on Windows",
      json: "",
      statusCode: 0,
    };
    if (ze.type() !== "Windows_NT")
      return (
        (v.details = "Driver Install Only Avaliable on Windows"),
        (v.statusCode = -1),
        u && V(v),
        v
      );
    let h = u
      ? "Install"
      : await p.window.showWarningMessage(
          "VEX drivers may be missing, would you like to install VEX drivers?",
          "Install",
          "Ignore"
        );
    if (h === "Install") {
      if (!s.exist) {
        let y = await s.download();
        if (y.statusCode !== 200) return V(y), y;
      }
      let P = await s.run();
      (v.statusCode = P.exitCode),
        P.exitCode === 0
          ? (v.details = "Drivers Installed")
          : (v.details = `Drivers Not Installed - ${P.stderr}`);
    } else (v.statusCode = 0), (v.details = "Driver Install Ignored");
    return V(v), v;
  }
  async function Ci() {
    if (
      !i.Extension.Context.isDevEnabled ||
      !(e.selectedDevice instanceof We || e.selectedDevice instanceof et)
    )
      return;
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    let u = p.Uri.file(ze.homedir()),
      v = {
        title: "Update Controller Radio",
        defaultUri: u,
        canSelectFolders: !1,
        canSelectFiles: !0,
        canSelectMany: !1,
        filters: {
          vexos: ["vexos"],
        },
      },
      h = await p.window.showOpenDialog(v);
    !h ||
      (V(await e.selectedDevice.controllerRadioUpdate(h[0])),
      e.checkControllerVEXOS(e.selectedDevice));
  }
  async function Ii() {
    if (
      !i.Extension.Context.isDevEnabled ||
      !(
        e.selectedDevice instanceof We ||
        e.selectedDevice instanceof et ||
        e.selectedDevice instanceof Et ||
        e.selectedDevice instanceof St
      )
    )
      return;
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    let u = p.Uri.file(ze.homedir()),
      v = {
        title: "Update Controller Radio",
        defaultUri: u,
        canSelectFolders: !1,
        canSelectFiles: !0,
        canSelectMany: !1,
        filters: {
          vexos: ["vexos"],
        },
      },
      h = await p.window.showOpenDialog(v);
    !h ||
      (V(await e.selectedDevice.controllerUsbUpdate(h[0])),
      e.checkControllerVEXOS(e.selectedDevice));
  }
  async function Pi() {
    if (
      !i.Extension.Context.isDevEnabled ||
      !(e.selectedDevice instanceof We || e.selectedDevice instanceof et)
    )
      return;
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    let u = p.Uri.file(ze.homedir()),
      v = {
        title: "Update Controller Radio",
        defaultUri: u,
        canSelectFolders: !1,
        canSelectFiles: !0,
        canSelectMany: !1,
        filters: {
          vexos: ["vexos"],
        },
      },
      h = await p.window.showOpenDialog(v);
    if (!h) {
      p.window.showWarningMessage("No VEXOS File Selected");
      return;
    }
    V(await e.selectedDevice.controllerUpdate(h[0]), !0),
      e.checkControllerVEXOS(e.selectedDevice);
  }
  async function _i() {
    if (
      !i.Extension.Context.isDevEnabled ||
      !(e.selectedDevice instanceof ft || e.selectedDevice instanceof vt)
    )
      return;
    if (!e.selectedDevice) {
      p.window.showWarningMessage("No Device Connected");
      return;
    }
    let u = p.Uri.file(ze.homedir()),
      v = {
        title: "Update Controller Radio",
        defaultUri: u,
        canSelectFolders: !1,
        canSelectFiles: !0,
        canSelectMany: !1,
        filters: {
          vexos: ["vexos"],
        },
      },
      h = await p.window.showOpenDialog(v);
    if (!h) {
      p.window.showWarningMessage("No VEXOS File Selected");
      return;
    }
    V(await e.selectedDevice.systemUpdate(h[0]), !0),
      e.checkSystemVEXOS(e.selectedDevice);
  }
  async function To() {
    let u = {
      command: i.Extension.Command.downloadID,
      details: "",
      statusCode: -1,
      json: "",
    };
    if (e.selectedDevice.bootMode !== I.BootMode.app) {
      (u.details = `${e.selectedDevice.platform} ${e.selectedDevice.device} in Bootloader (${e.selectedDevice.bootMode})`),
        t.appendLine(
          `[Command]: Download User Program, VEX ${e.selectedDevice.device}  in Bootloader (${e.selectedDevice.bootMode})`
        );
      let v = "",
        h = "";
      return (
        e.selectedDevice.device === i.Device.Brain
          ? ((v = `${e.selectedDevice.platform} ${e.selectedDevice.device} ${e.selectedDevice.bootMode} Detected.  Would you like to update?`),
            (h = "Update"))
          : ((v = `${e.selectedDevice.platform} ${e.selectedDevice.device} (DFU) Detected.  Would you like to recover?`),
            (h = "Recover")),
        p.window.showInformationMessage(v, h).then((P) => {
          P === "Recover" ? Vo() : P === "Update" && Eo();
        }),
        u
      );
    }
    return (u.statusCode = 0), u;
  }
})(Do || (Do = {}));
require("module-alias/register");

function pr(_) {
  let t = new qe(_, "VEX", "vex.main.debuglog");
  t.appendLine(`VEX Extension Version: ${i.Extension.version()}`),
    Fo.setup(_),
    Do.setup(_, t).catch((e) => {
      vi.window.showErrorMessage(`Fatal Error: ${e.message}`),
        t.appendLine(`VEX Extension Fatal Error: 
Name	:${e.name}
Message:	${e.message}
Stack:	${e?.stack}`);
    });
}
async function mr() {
  await Do.shutDown();
}
0 &&
  (module.exports = {
    activate,
    deactivate,
  });
//# sourceMappingURL=extension.js.map
