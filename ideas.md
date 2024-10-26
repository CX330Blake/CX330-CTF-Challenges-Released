1. Python private class access

    ```python
    class Challenge:
        def __init__(self, flag):
            self.__flag = "FLAG{FAKE_FLAG}"

    chal = Challenge()

    print(chal._Challenge__flag)
    ```
