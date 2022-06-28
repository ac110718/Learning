## Chapter 1
Recommendation systems must match consumption. Some things can be recommended repeatedly, like food. Others like books or music can only be recommended until purchased.
Thin line between recommendations and advertisements. Key is trust and relevancy. Advertisements are good for the publisher, recommendations are good for the consumer. Advertisements are usually claims of a good offer, can be targeted towards specific audiences, but not usually based on user behavior or with total lack of sponsorship. Recommendations are purely to drive conversion.

Recommendation is calculated based on what the active user likes, what others have liked in the past, and what's often requested by the receiver. A commercial is given for the benefit of the sender and is usually pushed on the receiver.

Recommender systems help users discover the long tail.

When trying to optimize for diversity over accuracy, you can try to separate out by category specific recommendations, and then within that set of content, set a ranking.

Recommendations could be based on specific time of day (Sunday mornings vs. evenings), or particular context (device, geo), or boost "freshness" with a time decay ranking algorithm

Collaborative filtering employs *usage* data, while content-based filtering employs content metadata and user profiles. A mix of these two is called hybrid recommenders.

Collaborative filtering needs much feedback from users to work properly while content-based filtering needs good descriptions of the items.

## Chapter 2

Events and behaviors need to be collected to provide an indication of users tastes. Mouseovers and detail views are strong indications of interest.

Timing is tricky. If you leave immediately and never come back, it's a strong sign of disinterest, but if you come back it's the exact opposite.
