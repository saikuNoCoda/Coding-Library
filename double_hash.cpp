void doHash(string &s,ll flag){
    pair<ll,ll> h = {0,0};
 
    FOR(i,0,sz(s)-1){
        h.first = (h.first*29 + (s[i]-'a'+1))%MOD;
        h.second = (h.second*29 + (s[i]-'a'+1))%(MOD+2);
    }
 
    if(flag == 1) h1 = h;
    else h2 = h;
}