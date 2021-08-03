package com.jnibridge.modules.dom;

public class Node {
    public int uniqueId;
    public String nodeName;
    public int nodeType;
    public String baseURI;
    Node(String nodeName, int nodeType, int uniqueId) {
        this.nodeName = nodeName;
        this.nodeType = nodeType;
        this.uniqueId = uniqueId;
    }
}
