def enfiler(chaine, val):
    chaine += ";"+val
    return chaine

def defiler(chaine):
    L = chaine.split(';')
    if len(L) == 0: return "", -1
    
    chaine = ';'.join(L[1:])
    return chaine, L[0]
