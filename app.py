import os
import sys
import json
import subprocess

from pyblish import api
from pyblish_qml.ipc import service


def log(message):
    print("py: %s" % message)


def listen(service):
    for line in iter(popen.stdout.readline, ""):
        try:
            response = json.loads(line)
        except Exception:
            # Regular message
            sys.stdout.write(line)
        else:
            is_request = (
                isinstance(response, dict) and
                response["header"] == "pyblish-qml:popen.request-1.0"
            )

            if is_request:
                payload = response["payload"]

                func = getattr(service, payload["name"])
                args = payload.get("args", [])
                result = func(*args)

                data = json.dumps({
                    "header": "pyblish-qml:popen.response",
                    "payload": result
                })

                popen.stdin.write(data + "\n")
                popen.stdin.flush()
            else:
                sys.stdout.write(line)


if __name__ == '__main__':
    api.register_plugin_path(os.getcwd())

    dirname = os.path.dirname(__file__)
    fname = os.path.join(
        dirname,
        "..",
        "build-temp-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug",
        "debug",
        "temp.exe"
    )

    log("Launching %s" % dirname)
    popen = subprocess.Popen(
        [fname],

        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        stdin=subprocess.PIPE,

        universal_newlines=True,
    )

    log("Listening on C++ program..")
    service = service.MockService()
    listen(service)
    log("Good bye")
