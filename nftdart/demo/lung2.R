
library(nftdart, lib.loc="/Users/mehribmp/Library/R/dev/arm64/4.3/library") ##Loading the nftbart package with a specific library location.

B=8 ##Setting the number of CPU cores for parallel processing to 8 (B=8).
options(mc.cores=B)

data(lung) ##Loading the "lung" dataset, which is often used for survival analysis in R.
N=length(lung$status) ##Calculating the number of observations (N) based on the "status" variable in the "lung" dataset.

##lung$status: 1=censored, 2=dead
##delta: 0=censored, 1=dead ##Defining the "delta" variable to indicate censoring (0) and death (1) based on the "status" variable.
delta=lung$status-1

## this study reports time in days rather than weeks or months
times=lung$time
times=times/7  ## weeks,Converting the time variable from days to weeks

## matrix of covariates
x.train=cbind(lung[ , -(1:3)]) ##Creating a matrix of covariates (x.train) by excluding the first three columns of the "lung" dataset.
## lung$sex:        Male=1 Female=2

set.seed(99) ##Setting a random seed for reproducibility.
post=nft2(x.train, x.train, times, delta, K=0) ##Running a survival analysis using the nft2 function with relevant data and parameters, including K=0.

x.test = rbind(x.train, x.train) ##Preparing the test data for prediction.
x.test[ , 2]=rep(1:2, each=N)
K=100
events=c(0, quantile(times[delta==1], (0:(K-1))/(K-1)))
a=proc.time()
pred = predict(post, x.test, x.test, K=K, events=events[-1], ##Calculating the prediction with the predict function, specifying K (number of events), and other options.
               XPtr=TRUE, FPD=TRUE)
print((proc.time()-a)/60)

plot(events, c(1, pred$surv.fpd.mean[1:K]), type='l', col=4, ##Plotting the results, including survival curves and confidence intervals for different groups.
     ylim=0:1,
     xlab=expression(italic(t)), sub='weeks',
     ylab=expression(italic(S)(italic(t), italic(x))))
lines(events, c(1, pred$surv.fpd.upper[1:K]), lty=2, lwd=2, col=4)
lines(events, c(1, pred$surv.fpd.lower[1:K]), lty=2, lwd=2, col=4)
lines(events, c(1, pred$surv.fpd.mean[K+1:K]), lwd=2, col=2)
lines(events, c(1, pred$surv.fpd.upper[K+1:K]), lty=2, lwd=2, col=2)
lines(events, c(1, pred$surv.fpd.lower[K+1:K]), lty=2, lwd=2, col=2)
legend(90, 0.95, c('NFT BART', 'Mortality',
                     'Males', 'Females'), lwd=2, col=c(0, 0, 4, 2), lty=1) ##Adding a legend and reference lines to the plot.
abline(h=0:1, v=0)
