#!/usr/bin/env bash
set -e
echo "============== Worst Build System ============="
echo "|"
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
