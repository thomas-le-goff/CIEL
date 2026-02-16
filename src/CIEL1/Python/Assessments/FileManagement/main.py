import re
from datetime import datetime

# Vous n'avez pas à modifier cette fonction, uniquement l'utiliser
def parse_log_line(line: str) -> dict:
    """
    Parse une ligne de log HTTP et retourne un dictionnaire contenant :
    - datetime : objet datetime
    - ip : adresse IP source
    - request : requête HTTP complète
    - status_code : code HTTP (int)
    - user_agent : user agent
    - is_suspicious : booléen indiquant si la requête est suspecte
    """

    pattern = re.compile(
        r'(?P<ip>\d+\.\d+\.\d+\.\d+)\s+-.*?\[(?P<datetime>[^\]]+)\]\s+"(?P<request>[^"]+)"\s+(?P<status>\d+)\s+\d+\s+"[^"]*"\s+"(?P<agent>[^"]*)"'
    )

    match = pattern.match(line.strip())
    if not match:
        raise ValueError(f"Format de log invalide : {line}")

    ip = match.group("ip")
    request = match.group("request")
    status_code = int(match.group("status"))
    user_agent = match.group("agent")

    raw_datetime = match.group("datetime").split()[0]
    date_heure = datetime.strptime(raw_datetime, "%d/%b/%Y:%H:%M:%S")

    suspicious_patterns = [
        "UNION SELECT",
        " OR ",
        "../",
        "<script>",
        "sqlmap",
        "nikto",
        "curl/"
    ]

    is_suspicious = False

    for pattern in suspicious_patterns:
        if pattern.lower() in request.lower() or pattern.lower() in user_agent.lower():
            is_suspicious = True
            break

    if "/login" in request and status_code == 401:
        is_suspicious = True

    return {
        "datetime": date_heure,
        "ip": ip,
        "request": request,
        "status_code": status_code,
        "user_agent": user_agent,
        "is_suspicious": is_suspicious
    }


def main():
# Retirez le mot "pass" est commencez à taper votre code ici
    pass

if __name__ == "__main__":
    main()