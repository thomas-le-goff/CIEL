import yara_x


def main():
    compiler = yara_x.Compiler()
    compiler.add_source('''
    rule php_anuna
    {
        meta:
            author      = "Vlad https://github.com/vlad-s"
            date        = "2016/07/18"
            description = "Catches a PHP Trojan"
        strings:
            $a = /<\?php \$[a-z]+ = '/
            $b = /\$[a-z]+=explode\(chr\(\([0-9]+[-+][0-9]+\)\)/
            $c = /\$[a-z]+=\([0-9]+[-+][0-9]+\)/
            $d = /if \(!function_exists\('[a-z]+'\)\)/
        condition:
            all of them
    }
    ''')

    rules = compiler.build()

    scanner = yara_x.Scanner(rules)

    try:
        result = scanner.scan_file("./php_anuna.php")

        if result.matching_rules:
            print("Match found:\n")
            for rule in result.matching_rules:
                print(f"Rule: {rule.identifier}")
                for pattern in rule.patterns:
                    for match in pattern.matches:
                        print(f"  Pattern: {pattern.identifier}")
                        print(f"  Offset: {match.offset}")
        else:
            print("File OK.")

    except yara_x.ScanError as err:
        print(err)


if __name__ == "__main__":
    main()
