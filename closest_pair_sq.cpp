
#define pii pair<ll,ll>
#define x first
#define y second

ll n;
//Comparator to maintain points sorted by y coordinate
struct comp {
    bool operator() (pii p, pii q) {
        return pii(p.y, p.x) < pii(q.y, q.x);
    }
};

set<pii, comp> box; //Stores processed points ordered by y coordinate

inline double dist(pii p, pii q) {
    p.x -= q.x;
    p.y -= q.y;
    return sqrt(p.x * 1.* p.x + p.y * 1.* p.y);
}

//O(N lg N)
//Returns the distance between the closest pair of points in ar[]
double closest_pair() {
    double best = 3e18;
    box.clear();

    sort(ar, ar + n); //Sort points by x coordinates

    box.insert(ar[0]);
    int j = 0; //Pointer to the first point inside the box

    for(int i = 1; i < n; i++) {
        while(j < i && ar[i].x - ar[j].x > best)
            box.erase(ar[j++]);

        auto it = box.lower_bound({0, ar[i].y - best});

        //This loop will run atmost 5 times
        while(it != box.end() && it -> y <= ar[i].y + best) {
            best = min(best, dist(*it, ar[i]));
            ++it;
        }

        box.insert(ar[i]);
    }
    return best;
} 
