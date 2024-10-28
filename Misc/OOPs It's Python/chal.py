from code import InteractiveConsole


class Challenge:
    __flag = r"FLAG{Y0u_C4n_5ti11_ac3ess_priVa7e_M3mb3r_In_Py7h0n}"


if __name__ == "__main__":
    chal = Challenge()
    test = "Hello World"
    console = InteractiveConsole(locals=locals())
    console.interact("Welcome to the challenge!")
