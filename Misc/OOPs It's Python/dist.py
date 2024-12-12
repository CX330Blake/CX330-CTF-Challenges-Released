from code import InteractiveConsole


class Challenge:
    __flag = r"flag{this_is_a_fake_flag}"


if __name__ == "__main__":
    chal = Challenge()
    console = InteractiveConsole(locals=locals())
    console.interact("Do you know what's OOP?")
