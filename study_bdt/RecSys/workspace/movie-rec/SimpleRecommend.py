# -*- coding: utf-8 -*-
from MovieGet import MovieLens
from surprise import SVD


def BuildAntiTestSetForUser(testSubject, trainset):
    fill = trainset.global_mean
    anti_testset = []
    u = trainset.to_inner_uid(str(testSubject))
    user_items = set([j for (j, _) in trainset.ur[u]])
    anti_testset += [(trainset.to_raw_uid(u), trainset.to_raw_iid(i), fill) for
                             i in trainset.all_items() if
                             i not in user_items]
    return anti_testset

testSubject = 85

ml = MovieLens()

print("Loading movie raiting...")
data = ml.loadMovieLensLatestSmall()

userRatings = ml.getUserRatings(testSubject)
loved = []
hated = []
for ratings in userRatings:
    if(float(ratings[1])>4.0):
        loved.append(ratings)
    if(float(ratings[1]) < 3.0):
        hated.append(ratings)
        

print("\nUser", testSubject, " loved these movies:" )
for ratings in loved:
    print(ml.getMovieName(ratings[0]))
    

print("\n and didn't like these movies")
for ratings in hated:
    print(ml.getMovieName(ratings[0]))
    

# 建立推荐模型
trainset = data.build_full_trainset()

algo = SVD()
algo.fit(trainset)

print("computing recommendations...")
testSet = BuildAntiTestSetForUser(testSubject, trainset)
predictions = algo.test(testSet)

recommendations = []

print ("\nWe recommend:")
for userID, movieID, actualRating, estimatedRating, _ in predictions:
    intMovieID = int(movieID)
    recommendations.append((intMovieID, estimatedRating))

recommendations.sort(key=lambda x: x[1], reverse=True)

for ratings in recommendations[:10]:
    print(ml.getMovieName(ratings[0]))