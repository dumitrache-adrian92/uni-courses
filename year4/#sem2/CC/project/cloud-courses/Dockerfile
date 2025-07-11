FROM node:lts-alpine AS builder

RUN apk add --no-cache autoconf automake libtool pkgconfig make g++

WORKDIR /app/website

ENV URL=http://localhost
ENV BASE_URL='/'

COPY --chown=node:node website/ /app/website

RUN chown node:node /app/website

USER node
RUN yarn install --audit
RUN yarn build

FROM nginx:alpine
COPY --from=builder /app/website/build /usr/share/nginx/html

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]

