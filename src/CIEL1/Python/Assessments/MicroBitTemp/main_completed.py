from microbit import *

snowflake = Image(
    "90909:"
    "09990:"
    "99999:"
    "09990:"
    "90909"
)

flam = Image(
    "00900:"
    "09990:"
    "99999:"
    "99999:"
    "09990"
)


def is_iterable_not_string(obj):
    try:
        iter(obj)
    except TypeError:
        return False
    return not isinstance(obj, (str, bytes))


def read_data_from_file(filename, default_value):
    """
    Lit des données depuis un fichier.

    Cette fonction tente d'ouvrir un fichier dont le nom est donné par
    le paramètre `filename` et d'en lire le contenu.

    Si le fichier contient une ou plusieurs valeurs, celles-ci sont
    retournées sous forme d'une valeur simple ou d'une liste, en
    fonction du type de `default_value`.

    Si le fichier n'existe pas ou ne peut pas être ouvert, le fichier
    est créé et la valeur par défaut est utilisée.

    Paramètres
    ----------
    filename : str
        Nom du fichier à lire (ou à créer s'il n'existe pas).

    default_value : any
        Valeur utilisée si le fichier n'existe pas ou est vide.
        Cette valeur permet aussi de déterminer si l'on attend
        une valeur simple ou une liste.

    Valeur de retour
    ----------------
    any
        La valeur lue depuis le fichier si elle existe,
        sinon la valeur par défaut.
    """
    result = []
    is_default_iter = is_iterable_not_string(default_value)
    try:
        with open(filename, 'r') as f:
            print(type(f))
            print(f.read())
            for l in f.read():
                result.append(l.strip())
            if len(result) == 0:
                return default_value
            return len(result) > 1 and not is_default_iter if result[0] else result
    except OSError:
        try:
            with open(filename, 'w') as f:
                f.write(str(default_value))
        except OSError:
            pass
    return default_value


def write_data_to_file(filename, value):
    """
    Écrit des données dans un fichier.

    Cette fonction ouvre (ou crée) un fichier dont le nom est donné
    par le paramètre `filename` et y écrit la valeur passée en paramètre.

    Si la valeur est une liste, chaque élément de la liste est écrit
    dans le fichier.
    Si la valeur est simple (nombre, texte), elle est écrite telle quelle.

    Le contenu précédent du fichier est écrasé.

    Paramètres
    ----------
    filename : str
        Nom du fichier dans lequel les données doivent être écrites.

    value : any
        Valeur à écrire dans le fichier. Peut être une valeur simple
        ou une liste.
    """
    is_value_iter = is_iterable_not_string(value)
    try:
        with open(filename, 'w') as f:
            if is_value_iter:
                for e in value:
                    f.write(str(value)+"\n")
            else:
                f.write(str(value))

    except OSError:
        pass


def load_from_files(default_value):
    # TODO (step 4)
    return default_value


def save_in_file(data):
    # TODO (step 4)
    pass


default_temp_info = {
    "max": -1,
    "min": -1,
    "values": []
}

temp_info = load_from_files(default_temp_info)
count = 0

while True:
    display.clear()

    presses = button_a.get_presses()

    if presses > 1:
        max = temp_info["max"]
        if max == -1:
            display.scroll("Aucune mesure", 50)
        else:
            display.scroll("Max : %s" % max, 50)

    elif presses > 0:
        min = temp_info["min"]
        if min == -1:
            display.scroll("Aucune mesure", 50)
        else:
            display.scroll("Min : %s" % min, 50)

    if accelerometer.was_gesture("shake"):
        values = temp_info["values"]
        l = len(values)
        if l > 0:
            display.scroll("Derniere temp : %s" % values[- 1], 50)
        else:
            display.scroll("Aucune mesure", 50)

    if pin_logo.is_touched():
        new_temp = temperature()
        temp_info["values"].append(new_temp)
        if temp_info["max"] == -1 or new_temp > temp_info["max"]:
            temp_info["max"] = new_temp
            display.show(flam)
        if temp_info["min"] == -1 or new_temp < temp_info["min"]:
            temp_info["min"] = new_temp
            display.show(snowflake)

    if button_b.was_pressed():
        load_from_files(default_temp_info)

    count += 1
    if count % 10 == 0:
        count = 0
        save_in_file(temp_info)

    sleep(1000)
