for((i = 1; i <= 20; i++)) do
    echo "Test $i"
    ./gen > in
    diff -w <(./main < in) <(./brute < in) || break
done