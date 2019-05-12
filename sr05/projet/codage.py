from common import log

def codage(what: str, who: str, where: str):
    return "{}/{}/{}\n".format(what, who, where)

def decodage(code: str):
    try:
        what, who, where = code.split('/')
        if where[-1] == '\n': where = where[:-1]
        return what, who, where
    except:
        log("", "code='{}'".format(code))


def decodage_what(what: str):
    if len(what)<1 or what[0] != '^' or what[-1] != '^':
        return {}

    result = {}

    variables = what[1:-1].split('^')

    for variable in variables:
        l = variable.split('~')
        if len(l) == 2:
            result[l[0]] = l[1]
        else:
            return {}

    return result

def codage_what(**kwargs):
    var = []
    for key, value in kwargs.items():
        var.append(str(key) + '~' + str(value))

    return '^' + '^'.join(var) + '^'
