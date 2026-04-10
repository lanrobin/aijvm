It seems that the current implement gc never stop the world, can you please add the implements. 

Following our rules, output ONLY the header definitions (`.hpp`) and brief architectural reasoning. Focus heavily on how the `ObjectHeader` accommodates the forwarding pointer, and how the cooperative STW handshake is synchronized. Do not write the full `.cpp` GC implementation yet.