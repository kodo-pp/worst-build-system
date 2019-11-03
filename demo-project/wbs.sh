#!/usr/bin/env bash
set -e
echo "============== Worst Build System ============="
echo "|"
case "$(( $RANDOM % 10 ))" in
    0)
        echo "|-> I'm tired, I gonna slee... zzz... zzz... zzz..."
        sleep 10
        ;;
    1)
        echo "|-> I don't like you"
        exit 69
        ;;
    2)
        echo "|-> Running 'export CXX=/bin/rm'"
        ;;
    3)
        for i in {1..5}; do
            echo "|"
            sleep 1
        done
        ;;
    4)
        echo '|-> WBS detected that your computer runs an operating system. This is unacceptable'
        exit 42
        ;;
    5)
        echo "|-> You didn't ask well"
        exit 1
        ;;
    6)
        echo "|-> Cannot build project because no"
        exit 1
        ;;
    7)
        echo "|-> WBS will terminate due to a fatal error. Error description: operation completed successfully"
        exit 0
        ;;
    8)
        true
        ;;
    9)
        exec sl
        ;;
esac
echo "|-> Compiling buildgen program"
"${CXX:-c++}" wbs.template.cpp -std=c++17 -o wbs.buildgen
echo "|-> Writing buildgen script"
cat > buildgen.sh << \EOF
#!/usr/bin/env bash
set -e
echo "============== Worst Build System ============="
echo "|"
echo "|-> Generating build script"
echo '#!/usr/bin/env bash
set -e
echo "============== Worst Build System ============="
echo "|"
echo "|-> Building"
PS4="|-> "
set -x' > wbs.BUILD
./wbs.buildgen >> wbs.BUILD
echo 'echo "|-> Done"' >> wbs.BUILD
chmod +x wbs.BUILD
echo "|-> Done"
EOF
chmod +x buildgen.sh
echo "|-> Done"
