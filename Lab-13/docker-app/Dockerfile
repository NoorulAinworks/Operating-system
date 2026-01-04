FROM node:lts-alpine3.23
COPY index.js .

COPY package.json .
COPY public ./public
RUN npm i
CMD ["node","index.js"]