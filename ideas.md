1. Python private class access

    ```python
    class Challenge:
        def __init__(self, flag):
            self.__flag = "FLAG{FAKE_FLAG}"

    chal = Challenge()

    print(chal._Challenge__flag)
    ```

    ```python
    class Animal:
    def __init__(self) -> None:
        self.__food = "apple"
        self._name = "Coco"
        self._owner = "Marry"

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, new_name):
        self._name = new_name

    def get_food(self):
        return self.__food

    def set_food(self, food):
        self.__food = food

    @staticmethod
    def talk():
        print("HIHIHII")

    dog = Animal()
    print(dog._name)
    print(dog.name)
    Animal.talk()
    print(dog._Animal__food)
    ```
