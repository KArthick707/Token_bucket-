simple Source {
    parameters:
        @display("i=block/departure,,0");
    gates:
        output out;
}

simple Destination {
    parameters:
        @display("i=block/buffer,,0");
    gates:
        input in;
}

simple Server {
    parameters:
        @display("i=block/server,,0");
        int token_limit;
        int queue_limit;
    gates:
        input in;
        output out;
}

network traffic_shaper {
    @display("bgb=709,270");
    submodules:
        source: Source {
            @display("i=device/pc2;p=156,148");
        }
        destination: Destination {
            @display("i=device/pc3,gold;p=520,148");
        }
        server: Server {
            @display("i=old/server1,black;p=321,148");
        }
    connections:
        source.out --> { datarate = 10Mbps; } --> server.in;
        server.out --> { datarate = 10Mbps; } --> destination.in;
}
