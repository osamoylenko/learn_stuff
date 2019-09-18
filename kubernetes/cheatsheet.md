```
выбрать нужный контекст
pip install awscli
aws configure
aws eks update-kubeconfig --name ...
kubectl config use-context ...

kubectl get pods
kubectl get pods --all-namespaces

kubectl exec -it [container] redis-cli
kubectl port-forward [container] 6379:6379


heml init
для запуска отдельного чарта helm -f 
helm template [путь]
```