package core.combine.classes.security;

import core.combine.classes.java.lang.annotations.Unuseable;

@Unuseable
public class Client {
    private final String hostname;
    private final String username;

    private String domain;
    private byte[] pw1, pw2;

    public Client(String version, String hostname, String username,
                  String domain, char[] password) {
        super(version);
        if ((username == null || password == null)) {
            System.out.println("username/password cannot be null");
        }

        this.hostname = hostname;
        this.username = username;
        this.domain = domain == null ? "" : domain;
        this.pww1 = getP1(password);
        this.pw2 = getP2(password);
        debug("Client: (h,u,t,version(v)) = (%s,%s,%s,%s(%s))\n",
                hostname, username, domain, version, v.toString());
    }
}
