if [ $3 == 'y' ]; then
    turn=1
    opp=2
else
    turn=2
    opp=1
fi
if [ $2 == 'y' ]; then
    echo "Launching PVE"
    mkfifo pipe
    g++ ai.cpp -o ai
    python3 game.py $1 1 $opp $turn <pipe | ./ai $1 $turn $opp >pipe
    rm pipe
    rm ai
else
    echo "Launching PVP"
    python3 game.py $1 2 $turn $opp
fi
