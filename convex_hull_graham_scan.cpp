struct pt{
    int x, y;

    bool operator == (const pt &p) const {
        return x == p.x and y == p.y;
    }
};

bool cw(const pt &a, const pt &b, const pt &c)
{
    return (b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x) > 0;
}

bool acw(const pt &a, const pt &b, const pt &c)
{
    return (b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x) < 0;
}

bool onSegment(const pt &a, const pt &b, const pt &c)
{
    return (b.y-a.y)*(c.x-b.x) == (c.y-b.y)*(b.x-a.x);
}

bool comp(const pt &a, const pt &b)
{
    return (a.x < b.x) or (a.x == b.x and a.y < b.y);
}

vector<pt> convex_hull(vector<pt> v)
{
    if(v.size() < 2){
        return v;
    }

    sort(v.begin(), v.end(), comp);

    pt left = v[0], right = v.back();

    vector<pt> up, down;
    up.pb(left);
    down.pb(left);

    for(int i=1;i<v.size();i++)
    {
        // if clockwise
        if(i==v.size()-1 or cw(left, v[i], right))
        {
            // remove the points which cur point will include
            while(up.size()>1 and !cw(up[up.size()-2], up[up.size()-1], v[i]))
            {
                up.pop_back();
            }
            up.pb(v[i]);
        }
        // if anticlockwise
        if(i==v.size()-1 or acw(left, v[i], right))
        {
            while(down.size()>1 and !acw(down[down.size()-2], down[down.size()-1], v[i]))
            {
                down.pop_back();
            }
            down.pb(v[i]);
        }
    }

    v.clear();
    //stroing anti-clockwise. For clockwise first up then down
    for(int i=0; i< down.size(); i++){
        v.pb(down[i]);
    }
    for(int i=up.size()-2; i>0;i--){
        v.pb(up[i]);
    }
    
    return v;
}

bool insideHull(const vector<pt>& hull, const pt &p)
{
    vector<pt> v = hull;
    v.pb(p);
    v = convex_hull(v);
    return find(v.begin(), v.end(), p) == v.end();
}

int countInside(const vector<pt> &hull, const vector<pt> &v)
{
    int c = 0;
    for(int i=0;i<v.size();i++)
    {
        if(insideHull(hull, v[i])) c++;
    }
    return c;
}
