# This extra script somehow solves test uploading crashing idk
# https://github.com/platformio/platformio-core/issues/3742
import time

Import("env")

if "test" in env.GetBuildType():
    env.AddPostAction("upload", lambda *_, **__: time.sleep(2))
