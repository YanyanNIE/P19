from sys import stderr

def log(verbose, NAME, message):
    if verbose:
        stderr.write("\n\n[BEGIN]MACHINE: '{}'\n -> MESSAGE: {}[END]\n".format(NAME, message))
        stderr.flush()
