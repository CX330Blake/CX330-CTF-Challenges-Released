from code import InteractiveConsole


class Challenge:
    __flag = r"HTB{7h3re's_N0_R34L_Pr1va7e_m3m6er_1n_Py7h0n}"


if __name__ == "__main__":
    chal = Challenge()
    console = InteractiveConsole(locals=locals())
    console.interact("Do you know what's OOP?")
